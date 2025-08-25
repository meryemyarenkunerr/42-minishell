/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_safe_readline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:53:40 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/25 12:20:48 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static ssize_t	readn(int fd, void *buf, size_t n)
{
	ssize_t	ret;
	size_t	read_total;
	char	*p;

	p = (char *)buf;
	read_total = 0;
	while (read_total < n)
	{
		ret = read(fd, p + read_total, n - read_total);
		if (ret <= 0)
			return (ret);
		read_total += (size_t)ret;
	}
	return ((ssize_t)read_total);
}

static void	write_line_to_pipe(int wfd, char *line)
{
	size_t	len;

	if (!line)
	{
		close(wfd);
		exit(0);
	}
	len = ft_strlen(line);
	if (write(wfd, &len, sizeof(len)) != (ssize_t) sizeof(len))
	{
		free(line);
		close(wfd);
		exit(0);
	}
	if (len > 0 && write(wfd, line, len) != (ssize_t)len)
	{
		free(line);
		close(wfd);
		exit(0);
	}
	free(line);
	close(wfd);
	exit(0);
}

static int	handle_wait_status(int status, t_shell *shell)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_sigint_received = AFTER_HEREDOC;
		shell->exit_status = 130;
		handle_signals();
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_sigint_received = AFTER_HEREDOC;
		shell->exit_status = 130;
		handle_signals();
		return (1);
	}
	return (0);
}

static char	*parent_receive(int rfd, pid_t pid, t_shell *shell)
{
	int		status;
	size_t	len;
	char	*result;

	if (waitpid(pid, &status, 0) == -1)
		return (close(rfd), NULL);
	if (handle_wait_status(status, shell))
		return (close(rfd), NULL);
	if (readn(rfd, &len, sizeof(len)) != (ssize_t) sizeof(len))
		return (close(rfd), NULL);
	result = (char *)malloc(len + 1);
	if (!result)
		return (close(rfd), NULL);
	if (len > 0 && readn(rfd, result, len) != (ssize_t)len)
		return (free(result), close(rfd), NULL);
	result[len] = '\0';
	close(rfd);
	return (result);
}

char	*safe_readline(const char *prompt, t_shell *shell,
		char *content, int fds[2])
{
	int		pipefd[2];
	pid_t	pid;
	char	*line;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid < 0)
		return (close(pipefd[0]), close(pipefd[1]), NULL);
	if (pid == 0)
	{
		close(fds[0]);
		close(fds[1]);
		close(pipefd[0]);
		free_at_exit(shell);
		free(content);
		g_sigint_received = IN_READLINE;
		handle_signals();
		line = readline(prompt);
		write_line_to_pipe(pipefd[1], line);
	}
	close(pipefd[1]);
	return (parent_receive(pipefd[0], pid, shell));
}

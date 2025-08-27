/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:53:40 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/27 06:00:57 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static ssize_t	readn(int fd, void *buf, size_t n)
{
	size_t	total;
	ssize_t	ret;

	total = 0;
	while (total < n)
	{
		ret = read(fd, (char *)buf + total, n - total);
		if (ret <= 0)
			return (ret);
		total += (size_t)ret;
	}
	return ((ssize_t)total);
}

static ssize_t	writen(int fd, const void *buf, size_t n)
{
	size_t	total;
	ssize_t	ret;

	total = 0;
	while (total < n)
	{
		ret = write(fd, (const char *)buf + total, n - total);
		if (ret <= 0)
			return (-1);
		total += (size_t)ret;
	}
	return ((ssize_t)total);
}

static void	child_process(int wfd, const char *prompt)
{
	char	*line;
	size_t	len;

	g_sigint_received = IN_READLINE;
	handle_signals();
	line = readline(prompt);
	if (!line)
	{
		close(wfd);
		exit(0);
	}
	len = ft_strlen(line);
	if (writen(wfd, &len, sizeof(len)) < 0
		|| (len > 0 && writen(wfd, line, len) < 0))
	{
		free(line);
		close(wfd);
		exit(0);
	}
	free(line);
	close(wfd);
	exit(0);
}

static char	*parent_process(int rfd, pid_t pid, t_shell *shell)
{
	int		status;
	size_t	len;
	char	*buf;

	if (waitpid(pid, &status, 0) == -1)
		return (close(rfd), NULL);
	if (handle_wait_status(status, shell))
		return (close(rfd), NULL);
	if (readn(rfd, &len, sizeof(len)) != (ssize_t) sizeof(len))
		return (close(rfd), NULL);
	buf = (char *)malloc(len + 1);
	if (!buf)
		return (close(rfd), NULL);
	if (len > 0 && readn(rfd, buf, len) != (ssize_t)len)
	{
		free(buf);
		close(rfd);
		return (NULL);
	}
	buf[len] = '\0';
	close(rfd);
	return (buf);
}

char	*read_line(const char *prompt, t_shell *shell, char *content,
	int fds[2])
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (NULL);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		close(fds[0]);
		close(fds[1]);
		free_at_exit(shell);
		free(content);
		child_process(pipefd[1], prompt);
	}
	close(pipefd[1]);
	return (parent_process(pipefd[0], pid, shell));
}

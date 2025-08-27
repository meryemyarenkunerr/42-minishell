/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_safe_readline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:53:40 by kbatur            #+#    #+#             */
/*   Updated: 2025/08/26 23:59:00 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

// readn: tam n byte okuyana kadar döner (EOF/hata -> ret <= 0)
static ssize_t	readn(int fd, void *buf, size_t n)
{
	size_t	total = 0;
	ssize_t	ret;

	while (total < n)
	{
		ret = read(fd, (char *)buf + total, n - total);
		if (ret <= 0)
			return (ret);
		total += (size_t)ret;
	}
	return ((ssize_t)total);
}

// writen: tam n byte yazana kadar döner (hata -> -1)
static ssize_t	writen(int fd, const void *buf, size_t n)
{
	size_t	total = 0;
	ssize_t	ret;

	while (total < n)
	{
		ret = write(fd, (const char *)buf + total, n - total);
		if (ret <= 0)
			return -1;
		total += (size_t)ret;
	}
	return (ssize_t)total;
}

static void	child_process(int wfd, const char *prompt)
{
	char	*line;
	size_t	len;

	// SINYAL DURUMU: readline öncesi
	g_sigint_received = IN_READLINE;
	handle_signals();

	line = readline(prompt);

	// Ctrl+D (line == NULL) -> ORİJİNAL DAVRANIŞ: HİÇBİR ŞEY YAZMADAN pipe'ı kapat
	if (!line)
	{
		close(wfd);
		exit(0);
	}

	len = ft_strlen(line);
	if (writen(wfd, &len, sizeof(len)) < 0 || (len > 0 && writen(wfd, line, len) < 0))
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

	// Çocuk Ctrl+D ile hiçbir şey yazmadıysa burası başarısız olur -> NULL döneriz (orijinal davranış)
	if (readn(rfd, &len, sizeof(len)) != (ssize_t)sizeof(len))
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

char	*safe_readline(const char *prompt, t_shell *shell, char *content, int fds[2])
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
		// ÇOCUK: sadece pipe'ın yazma ucunu kullanacak
		close(pipefd[0]);
		// heredoc özel fd'lerini kapat (orijinal kodda vardı)
		close(fds[0]);
		close(fds[1]);
		// çocukta shell kaynaklarını bırak
		free_at_exit(shell);
		free(content);
		child_process(pipefd[1], prompt);
	}
	// EBEVEYN: sadece okuma ucunu kullanacak
	close(pipefd[1]);
	return (parent_process(pipefd[0], pid, shell));
}

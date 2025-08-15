#include "../../includes/minishell.h"

static int	create_heredoc_pipe(int	pipe_fds[2], t_shell *shell)
{
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		shell->exit_status = 1;
		return FALSE;
	}
	return TRUE;
}

static int	process_single_command(t_shell *shell, const char *delimeter)
{
	int		pipe_fds[2];
	pid_t	pid;
	int		result;

	if (!create_heredoc_pipe(pipe_fds, shell))
		return -1;
	signal(SIGINT, heredoc_signal_handler);
	pid = fork();
	if (pid == 0) // child
	{
		signal(SIGINT, SIG_DFL);
		heredoc_child_process(pipe_fds, delimeter);
	}
	else if (pid > 0)
	{
		close(pipe_fds[1]); // write end'i kapat
		result = heredoc_parent_process(pipe_fds, pid);
		signal(SIGINT, handle_sigint);
		return (result);
	}
	else
		return (fork_error_handler(pipe_fds, shell));
	return TRUE;
}

static int	process_heredoc_for_command(t_shell *shell, t_command *cmd)
{
	int	i;
	int	last_fd;

	i = 0;
	last_fd = -1;
	signal(SIGINT, heredoc_signal_handler);
	while (i < cmd->heredoc_count)
	{
		if (last_fd != -1) // her komuttan önce bir önceki fd'yi kapat
			close(last_fd);
		last_fd = process_single_command(shell, cmd->heredoc_delimeter[i]);
		if (last_fd == -1 || last_fd == FALSE) // pipe hatası
		{
			signal(SIGINT, handle_sigint);
			return FALSE;
		}
		i++;
	}
	cmd->fd_in = last_fd;
	signal(SIGINT, handle_sigint);
	return TRUE;

	//int		pipe_fds[2];
	//pid_t	pid;
	//int		result;

	//if (!create_heredoc_pipe(pipe_fds, shell))
	//	return FALSE;
	//signal(SIGINT, heredoc_signal_handler); // parent'ta SIGINT'i ignore et
	//pid = fork();
	//if (pid == 0) // child process
	//{
	//	signal(SIGINT, SIG_DFL); // child'da signal'ı restore et
	//	heredoc_child_process(pipe_fds, cmd->heredoc_delimeter[0]);
	//}
	//else if (pid > 0) // parent process
	//{
	//	result = (heredoc_parent_process(pipe_fds, cmd, pid));
	//	signal(SIGINT, handle_sigint); // signal handler'ı restore et
	//	return (result);
	//}
	//else
	//	return (fork_error_handler(pipe_fds, shell));
	//return TRUE;
}

int	handle_heredocs(t_shell *shell)
{
	t_command	*curr;

	curr = shell->commands;
	while (curr)
	{
		if (curr->heredoc_count > 0)
		{
			if (!process_heredoc_for_command(shell, curr))
				return FALSE;
		}
		curr = curr->next;
	}
	return TRUE;
}
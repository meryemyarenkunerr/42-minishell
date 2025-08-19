#include "../../includes/minishell.h"

void	cleanup_pipeline(t_shell *shell, int **pipes, pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_exit_status;

	last_exit_status = 0;
	close_all_pipes_in_parent(pipes, cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			perror("waitpid");
		else
		{
			if (i == cmd_count - 1)
			{
				if (WIFEXITED(status))
					last_exit_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_exit_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	shell->exit_status = last_exit_status;
	cleanup_pipes(pipes, cmd_count);
	free(pids);
}

void	cleanup_pipes(int **pipes, int cmd_count)
{
	int	i;
	int	pipe_count;

	if (!pipes)
		return ;

	pipe_count = cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	cleanup_partial_pipes(int **pipes, int created_count)
{
	int	i;

	if (!pipes)
		return ;

	i = 0;
	while (i < created_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

void	cleanup_partial_processes(pid_t *pids, int created_count)
{
	int	i;
	int	status;

	if (!pids)
		return ;
	i = 0;
	while (i < created_count)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
}
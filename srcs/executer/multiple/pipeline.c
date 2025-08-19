#include "../../../includes/minishell.h"

void setup_pipeline_child(t_command *cmd, int **pipes, int cmd_count, int cmd_index)
{
	if (cmd_index > 0)
	{
		if (cmd->fd_in == STDIN_FILENO)
			dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < cmd_count - 1)
	{
		if (cmd->fd_out == STDOUT_FILENO)
			dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_all_pipes_in_child(pipes, cmd_count);
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

pid_t	*execute_pipeline_processes(t_shell *shell, int **pipes, int cmd_count)
{
	pid_t		*pids;
	t_command	*current_cmd;
	int			i;

	pids = malloc(cmd_count * sizeof(pid_t));
	if (!pids)
		return (NULL);

	current_cmd = shell->commands;
	i = 0;
	while (i < cmd_count && current_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			cleanup_partial_processes(pids, i);
			return (NULL);
		}
		if (pids[i] == 0)
		{
			setup_pipeline_child(current_cmd, pipes, cmd_count, i);
			execute_pipeline_child(shell, current_cmd);
			exit(127);
		}
		current_cmd = current_cmd->next;
		i++;
	}
	return (pids);
}

int	**create_pipeline_pipes(int cmd_count)
{
	int	**pipes;
	int	i;
	int	pipe_count;

	pipe_count = cmd_count - 1;
	pipes = malloc(pipe_count * sizeof(int*));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			cleanup_partial_pipes(pipes, i);
			return (NULL);
		}

		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free(pipes[i]);
			cleanup_partial_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

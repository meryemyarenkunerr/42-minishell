#include "../../includes/minishell.h"

void	execute_pipeline_commands(t_shell *shell, int cmd_count)
{
	int		**pipes;
	pid_t	*pids;

	if (!shell || !shell->commands || cmd_count < 2)
		return ;

	pipes = create_pipeline_pipes(cmd_count);
	if (!pipes)
	{
		shell->exit_status = 1;
		return ;
	}
	pids = execute_pipeline_processes(shell, pipes, cmd_count);
	if (!pids)
	{
		cleanup_pipes(pipes, cmd_count);
		shell->exit_status = 1;
		return;
	}
	cleanup_pipeline(shell, pipes, pids, cmd_count);
}
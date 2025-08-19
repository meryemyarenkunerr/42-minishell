#include "../../includes/minishell.h"

void	free_at_exit(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->environment)
	{
		free_env_list(shell->environment);
		shell->environment = NULL;
	}
	if (shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
	if (shell->pipeline)
	{
		free_pipeline(shell->pipeline);
		shell->pipeline = NULL;
	}
	rl_clear_history();
}

void	cleanup_previous_state(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
	if (shell->pipeline)
	{
		free_pipeline(shell->pipeline);
		shell->pipeline = NULL;
	}
}

#include "../../includes/minishell.h"

void	executer(t_shell *shell)
{
	if (!shell || !shell->pipeline)
		return ;
	if (shell->pipeline->count == 1)
		execute_single_command(shell, shell->commands);
	else
		execute_pipeline_commands(shell, shell->pipeline->count);
}

#include "../../../includes/minishell.h"

void	execute_pipeline_child(t_shell *shell, t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		exit(127);
	if (is_builtin_command(cmd->cmd))
	{
		execute_builtin(shell, cmd);
		exit(shell->exit_status);
	}
	else
		execute_external_in_pipeline(shell, cmd);
}

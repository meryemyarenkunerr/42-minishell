#include "../../includes/minishell.h"

void	execute_single_command(t_shell *shell, t_command *cmd)
{
	if (!shell || !cmd || !cmd->cmd)
		return ;
	if (is_builtin_command(cmd->cmd))
		execute_builtin(shell, cmd);
	else
		execute_external(shell, cmd);
}

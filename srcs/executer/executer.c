#include "../../includes/minishell.h"

void	executer(t_shell *shell)
{
	// t_command içini doldurma (input/output file ve append_mode)
	if (!filler_commands(shell))
	{
		shell->exit_status = 1;
		return ;
	}
	print_shell_info(shell);
}


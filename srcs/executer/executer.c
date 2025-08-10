#include "../../includes/minishell.h"

void	executer(t_shell *shell)
{
	// t_command içini doldurma (input/output file ve append_mode)
	filler_commands(shell->commands);
	print_shell_info(shell);
}


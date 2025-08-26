#include "../../includes/minishell.h"

void	pipes_creation_error(t_shell *shell)
{
	ft_putstr_fd("minishell: failed to create pipes\n", STDERR_FILENO);
	shell->exit_status = 1;
}
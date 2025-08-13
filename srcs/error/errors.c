#include "../../includes/minishell.h"

void	handle_export_error(t_shell *shell, const char *arg)
{
	printf("export `%s': not a valid identifier\n", arg);
	shell->exit_status = 1;
}
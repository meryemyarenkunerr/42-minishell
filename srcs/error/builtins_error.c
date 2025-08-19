#include "../../includes/minishell.h"

void	numeric_argument_error(t_shell *shell, t_command *cmd)
{
	printf("minishell: exit: %s: numeric argument required\n",
		cmd->arguments[1]);
	shell->exit_status = 2;
}

void	too_many_argument_error(t_shell *shell)
{
	printf("minishell: exit: too many arguments\n");
	shell->exit_status = 1;
}

void	unset_not_valid_identifier_error(t_shell *shell, t_command *cmd,
	int idx)
{
	printf("minishell: unset: `%s': not a valid identifier\n",
		cmd->arguments[idx]);
	shell->exit_status = 1;
}

#include "../includes/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->exit_status = 0;
	shell->environment = init_env(env);
}
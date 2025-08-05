#include "../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	if(!env)
		return ;
	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	free_at_exit(t_shell *shell)
{
	free_env_list(shell->environment);
}
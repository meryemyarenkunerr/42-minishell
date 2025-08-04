#include "../includes/minishell.h"

t_env	*init_env_node(t_env *new_env_node)
{

}

t_env	add_new_env_node(t_env *env_head, t_env *new_env_node)
{

}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*env_head;

	i = 0;
	env_head = init_env_node(env[i]);
	i++;
	while (env[i])
	{
		add_new_env_node(env_head, init_env_node(env[i]));
		i++;
	}
}
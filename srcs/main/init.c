#include "../../includes/minishell.h"

// void	init_simple_signal(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		g_sigint_received = 0;
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// void	init_signal(void)
// {
// 	signal(SIGINT, init_simple_signal);
// 	signal(SIGQUIT, SIG_IGN);
// }

t_env	*init_env(char **env)
{
	t_env	*head;
	int		i;

	head = NULL;
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!add_key_value_pair(&head, env[i]))
		{
			free_env_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

void	init_shell(t_shell *shell, char **env)
{
	if (!shell)
		return ;
	shell->environment = init_env(env);
	shell->exit_status = 0;
	shell->exit = FALSE;
	shell->commands = NULL;
	shell->pipeline = NULL;
	// init_signal();
	handle_signals();
}

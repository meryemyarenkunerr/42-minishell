#include "../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_at_exit(t_shell *shell)
{
	// terminal ayarlarını eski haline getirmek için
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term_backup) == -1)
		perror("tcsetattr");

	free_env_list(shell->environment);
	if (shell->prompt)
		free(shell->prompt);
	rl_clear_history();
}

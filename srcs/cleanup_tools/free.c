#include "../../includes/minishell.h"

void free_heredoc_delimiters(char **heredocs)
{
	if (!heredocs)
		return;
	for (int i = 0; heredocs[i]; i++)
		free(heredocs[i]);
	free(heredocs);
}

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
	if (shell->current_dir)
		free(shell->current_dir);
	if (shell->home_dir)
		free(shell->home_dir);
	if (shell->pipeline)
		free_pipeline_temp(shell->pipeline);
	if (shell->commands)
		free_command_temp(shell->commands);
	rl_clear_history();
}

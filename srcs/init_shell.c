#include "../includes/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->exit_status = 0;
	shell->environment = init_env(env);
	shell->prompt = NULL;
	shell->cmd_has_been_executed = TRUE;	// başlangıçta böyle kabul edelim ki sorun çıkmasın

	// terminal ayarlarını yedeklemek için
	if (tcgetattr(STDIN_FILENO, &shell->term_backup) == -1)
		perror("tcgetattr");
}
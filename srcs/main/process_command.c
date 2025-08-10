#include "../../includes/minishell.h"

int	process_command(t_shell *shell, char *command)
{
	(void)command;	// serhat kullanacak
	// tokenize et
	// pipeline'a ayır
	// komut yapısını oluştur
	// shell struct içindeki komut listesini ayarla

	// buradan itibaren benim bölümüm başlıyor
	if (shell->commands)
	{
		free_command_temp(shell->commands);
		shell->commands = NULL;
	}
	if (shell->pipeline)
	{
		free_pipeline_temp(shell->pipeline);
		shell->pipeline = NULL;
	}
	fill_shell_echo_append_temp(shell);
	executer(shell);
	// print_shell_info(shell);
	return TRUE;
}
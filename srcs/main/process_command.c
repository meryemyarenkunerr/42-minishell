#include "../../includes/minishell.h"

static void	initialize_command_fields(t_shell *shell)
{
	t_command	*curr;

	curr = shell->commands;
	while (curr)
	{
		curr->fd_in = STDIN_FILENO;
		curr->fd_out = STDOUT_FILENO;
		curr->pid = -1;
		curr = curr->next;
	}
}

int	process_command(t_shell *shell, char *command)
{
	(void)command;
	// tokenize et
	// pipeline'a ayır
	// komut yapısını oluştur
	// shell struct içindeki komut listesini ayarla
	// t_command ve t_pipeline doldurulmuş olacak

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
	fill_shell_cat_heredocs_temp(shell);
	initialize_command_fields(shell);
	executer(shell);
	return TRUE;
}
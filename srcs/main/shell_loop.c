#include "../../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*command;
	int		stat;

	while (1)
	{
		setup_signal_handler(&shell->term_backup);			// sinyal işlemleri ve terminal ayarı
		build_prompt(shell);								// prompt'un dinamik bir şekilde oluşturulması
		command = read_line(shell);
		stat = handle_signal_and_exit(shell, &command);
		if (stat == 0)
			break ;
		else if (stat == 1)
			continue ;
		if (!process_command(shell, command))
		{
			free(command);
			break ;
		}
		add_history(command);
		free(command);
	}
}

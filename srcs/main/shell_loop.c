#include "../../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*command;
	int		stat;

	setup_signal_handler();
	while (1)
	{
		g_sigint_received = 0;
		build_prompt(shell);								// prompt'un dinamik bir şekilde oluşturulması
		command = read_line(shell);
		if (command && ft_strlen(command) == 0)
		{
			free(command);
			continue ;
		}
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

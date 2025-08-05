#include "../includes/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*command;

	(void)shell;
	while (1)
	{
		setup_signal_handler();
		command = readline(PROMPT);
		if (!command) // Ctrl-D veya EOF
		{
			printf("bye bye <3\n");
			break ;
		}
		if(*command) // boş enter için
			add_history(command);

		printf("Komut: %s\n", command);
		free(command);
	}
}
#include "../../includes/minishell.h"

void	heredoc_signal_handler(int signo)
{
	if (signo == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
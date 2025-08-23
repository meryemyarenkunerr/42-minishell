#include "../../includes/minishell.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT && g_sigint_received == IN_HEREDOC)
	{
		g_sigint_received = SIGINT;
		write(STDERR_FILENO, "\n", 1);  // Newline ekle
	}
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	// SIGQUIT'i ignore et
	signal(SIGQUIT, SIG_IGN);

	// Heredoc moduna geç
	g_sigint_received = IN_HEREDOC;
}

void	restore_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

	// Default duruma döndür
	g_sigint_received = -1;
}
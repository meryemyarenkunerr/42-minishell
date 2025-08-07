#include "../includes/minishell.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sigint_received = TRUE;		// Ctrl+C'ye basıldı
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);			// input satırını siler
		rl_on_new_line();				// yeni satıra geçer
		rl_redisplay();					// promptu yeniden gösterir
	}
}

void	setup_signal_handler(struct termios *term_backup)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		modified;

	// terminal ayarları
	modified = *term_backup;
	modified.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified);

	// SIGINT
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);

	// SIGQUIT
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
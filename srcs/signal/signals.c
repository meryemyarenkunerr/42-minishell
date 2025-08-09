#include "../../includes/minishell.h"

int	handle_signal_and_exit(t_shell *shell, char **command)
{
	if (!*command)										// Ctrl-D veya EOF
	{
		printf("bye bye <3\n");
		return 0;										// shell'den çık
	}
	if (g_sigint_received)								// Ctrl+C ile komut iptal edildiyse
	{
		sigint_received(shell);
		free(*command);
		*command = NULL;
		return 1;										// döngü devam etsin
	}
	if (is_exit_command_received(shell, *command))		// exit komutu
	{
		free(*command);
		*command = NULL;
		return 0;										// shell'den çık
	}
	return 2;											// normal devam et
}

// Sinyal işlemi: Ctrl+C (SIGINT) geldiğinde promptu temizle ve yeni satır başlat
static void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sigint_received = TRUE;		// Ctrl+C'ye basıldı
		write(STDOUT_FILENO, "\n", 1);	// Yeni satır
		rl_replace_line("", 0);			// input satırını sil
		rl_on_new_line();				// yeni satıra geç
		rl_redisplay();					// promptu yeniden göster
	}
}

// Hata kontrolü: sistem çağrısı başarısızsa uyarı ver
static void	check_and_warn(int ret, const char *msg)
{
	if (ret == -1)
		perror(msg);
}

// Terminal ve sinyal ayarlarını yapılandır
void	setup_signal_handler(struct termios *term_backup)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		modified;

	// Terminalde ^C, ^\ gibi karakterlerin görünmesini engelle
	modified = *term_backup;
	modified.c_lflag &= ~ECHOCTL;
	check_and_warn(tcsetattr(STDIN_FILENO, TCSAFLUSH, &modified), "tcsetattr");

	// SIGINT (Ctrl+C) için özel handler ata
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	check_and_warn(sigaction(SIGINT, &sa_int, NULL), "sigaction(SIGINT)");

	// SIGQUIT (Ctrl+\) sinyalini yok say
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	check_and_warn(sigaction(SIGQUIT, &sa_quit, NULL), "sigaction(SIGQUIT)");
}
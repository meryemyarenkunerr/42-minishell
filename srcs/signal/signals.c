/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

// Hata kontrolü: sistem çağrısı başarısızsa uyarı ver
void	check_and_warn(int ret, const char *msg)
{
	if (ret == -1)
		perror(msg);
}

void	sigint_received(t_shell *shell)
{
	shell->exit_status = 130; // POSIX standardı (Ctrl+C için)
	g_sigint_received = FALSE;
}

// Sinyal işlemi: Ctrl+C (SIGINT) geldiğinde promptu temizle ve yeni satır başlat
void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_sigint_received = 1;			// Ctrl+C'ye basıldı
		write(STDOUT_FILENO, "\n", 1);	// Yeni satır
		rl_replace_line("", 0);			// input satırını sil
		rl_on_new_line();				// yeni satıra geç
		rl_redisplay();					// promptu yeniden göster
	}
}

// Terminal ve sinyal ayarlarını yapılandır
void	setup_signal_handler()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	// Terminal ayarları - ^C karakterini gizle
	if (tcgetattr(STDIN_FILENO, &term) != -1)
	{
		term.c_lflag &= ~ECHOCTL;  // Control karakterleri gizle
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	}

	// SIGINT (Ctrl+C) için özel handler ata
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa_int.sa_mask);
	check_and_warn(sigaction(SIGINT, &sa_int, NULL), "sigaction(SIGINT)");

	// SIGQUIT (Ctrl+\) sinyalini yok say
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	check_and_warn(sigaction(SIGQUIT, &sa_quit, NULL), "sigaction(SIGQUIT)");
}

int	handle_signal_and_exit(t_shell *shell, char **command)
{
	if (!*command)										// Ctrl-D veya EOF
	{
		//write(STDOUT_FILENO, "bye bye <3\n", 11);
		return 0;										// shell'den çık
	}
	if (g_sigint_received)								// Ctrl+C ile komut iptal edildiyse
	{
		sigint_received(shell);
		free(*command);
		*command = NULL;
		return 1;										// döngü devam etsin
	}
	//if (is_exit_command_received(shell, *command))		// exit komutu
	//{
	//	free(*command);
	//	*command = NULL;
	//	return 0;										// shell'den çık
	//}
	return 2;											// normal devam et
}
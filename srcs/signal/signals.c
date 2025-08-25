/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 12:35:58 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sigint_received = 0;

// // Hata kontrolü: sistem çağrısı başarısızsa uyarı ver
// void	check_and_warn(int ret, const char *msg)
// {
// 	if (ret == -1)
// 		perror(msg);
// }

// void	sigint_received(t_shell *shell)
// {
// 	shell->exit_status = 130; // POSIX standardı (Ctrl+C için)
// 	g_sigint_received = FALSE;
// }

// // Sinyal işlemi: Ctrl+C (SIGINT)
// // geldiğinde promptu temizle ve yeni satır başlat
// void	handle_sigint(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		g_sigint_received = 1;			// Ctrl+C'ye basıldı
// 		write(STDOUT_FILENO, "\n", 1);	// Yeni satır
// 		rl_replace_line("", 0);			// input satırını sil
// 		rl_on_new_line();				// yeni satıra geç
// 		rl_redisplay();					// promptu yeniden göster
// 	}
// }

// // Terminal ve sinyal ayarlarını yapılandır
// void	setup_signal_handler()
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;
// 	struct termios		term;

// 	// Terminal ayarları - ^C karakterini gizle
// 	if (tcgetattr(STDIN_FILENO, &term) != -1)
// 	{
// 		term.c_lflag &= ~ECHOCTL;  // Control karakterleri gizle
// 		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
// 	}

// 	// SIGINT (Ctrl+C) için özel handler ata
// 	sa_int.sa_handler = handle_sigint;
// 	sa_int.sa_flags = SA_RESTART | SA_NODEFER;
// 	sigemptyset(&sa_int.sa_mask);
// 	check_and_warn(sigaction(SIGINT, &sa_int, NULL), "sigaction(SIGINT)");

// 	// SIGQUIT (Ctrl+\) sinyalini yok say
// 	sa_quit.sa_handler = SIG_IGN;
// 	sa_quit.sa_flags = SA_RESTART;
// 	sigemptyset(&sa_quit.sa_mask);
// 	check_and_warn(sigaction(SIGQUIT, &sa_quit, NULL), "sigaction(SIGQUIT)");
// }

// int	handle_signal_and_exit(t_shell *shell, char **command)
// {
// 	if (!*command)										// Ctrl-D veya EOF
// 	{
// 		//write(STDOUT_FILENO, "bye bye <3\n", 11);
// 		return 0;										// shell'den çık
// 	}
//  // Ctrl+C ile komut iptal edildiyse
//  if (g_sigint_received)								
// 	{
// 		sigint_received(shell);
// 		free(*command);
// 		*command = NULL;
// 		return 1;										// döngü devam etsin
// 	}
// 	//if (is_exit_command_received(shell, *command))		// exit komutu
// 	//{
// 	//	free(*command);
// 	//	*command = NULL;
// 	//	return 0;										// shell'den çık
// 	//}
// 	return 2;											// normal devam et
// }

void	ctrl_d(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\033[K");
	rl_redisplay();
	g_sigint_received = 0;
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_sigint_received == IN_HEREDOC)
	{
		write(1, "\n", 1);
		g_sigint_received = AFTER_HEREDOC;
		return ;
	}
	else if (g_sigint_received == IN_CMD)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_sigint_received = AFTER_CMD;
	}
	else if (g_sigint_received == IN_READLINE)
		exit(130);
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_sigint_received != AFTER_HEREDOC && g_sigint_received != AFTER_CMD)
		g_sigint_received = 1;
}

void	tcseta(void)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		return ;
	term1.c_cc[VQUIT] = _POSIX_VDISABLE;
	term1.c_lflag |= ECHOE | ICANON;
	term1.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
		return ;
}

void	handle_signals(void)
{
	tcseta();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}

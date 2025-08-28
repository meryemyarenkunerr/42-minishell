/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 11:29:35 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sigint_received = 0;

void	ctrl_d(int sig)
{
	(void)sig;
	if (g_sigint_received == IN_HEREDOC)
	{
		write(1, "\n", 1);
		g_sigint_received = AFTER_HEREDOC;
		return ;
	}
	else
	{
		rl_on_new_line();
		printf("\033[K");
		rl_redisplay();
		g_sigint_received = 0;
	}

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

// SIGPIPE handler tanımla (fonksiyon dışında):
void sigpipe_handler(int sig) {
	(void)sig;
    fprintf(stderr, "CHILD %d: SIGPIPE received!\n", getpid());
    exit(1);
}

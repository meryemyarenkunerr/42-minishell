/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 12:22:50 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
#define MINISHELL_SIGNAL_H

#include "../structs.h"

/* SIGNAL */
///* signals.c*/
//int handle_signal_and_exit(t_shell *shell, char **command);
//void check_and_warn(int ret, const char *msg);
//void handle_sigint(int signo);
//void sigint_received(t_shell *shell);
//void heredoc_signal_handler(int signo);

/* signals.c */
void			handle_signals(void);
void			ctrl_c(int sig);
void			ctrl_d(int sig);
void			tcseta(void);

/* heredoc_signal.c */
void			heredoc_signal_handler(int signo);
void			setup_heredoc_signals(void);
void			restore_heredoc_signals(void);


#endif // MINISHELL_SIGNAL_H

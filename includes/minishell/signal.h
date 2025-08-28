/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:30:13 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:30:15 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../structs.h"

void	handle_signals(void);
void	ctrl_c(int sig);
void	ctrl_d(int sig);
void	tcseta(void);
void	heredoc_signal_handler(int signo);
void	setup_heredoc_signals(void);
void	restore_heredoc_signals(void);

#endif

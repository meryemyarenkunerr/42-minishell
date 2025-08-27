/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 08:09:20 by mkuner           ###   ########.fr       */
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

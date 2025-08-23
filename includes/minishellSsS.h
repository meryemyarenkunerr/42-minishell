/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:01:40 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 20:36:31 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard Libraries */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Own Headers */
# include "../libft/libft.h"
# include "defines.h"
# include "structs.h"
# include "./minishell/error.h"
# include "./minishell/cleanup.h"
# include "./minishell/executer.h"
# include "./minishell/e_builtins.h"
# include "./minishell/e_command.h"
# include "./minishell/e_external.h"
# include "./minishell/e_heredoc.h"
# include "./minishell/e_multiple.h"
# include "./minishell/main.h"
# include "./minishell/parser.h"

/* Global Variable */
extern int	g_sigint_received;

/* Functions */

/* SIGNAL */
/* signals.c */
int				handle_signal_and_exit(t_shell *shell, char **command);
void			check_and_warn(int ret, const char *msg);
void			handle_sigint(int signo);
void			sigint_received(t_shell *shell);

/* heredoc_signal.c */
void			heredoc_signal_handler(int signo);
void			setup_heredoc_signals(void);
void			restore_heredoc_signals(void);




void		print_shell_info(t_shell *shell);

#endif

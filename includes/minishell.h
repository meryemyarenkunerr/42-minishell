/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:01:40 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 11:27:12 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <termios.h>

# include "../libft/libft.h"
# include "defines.h"
# include "structs.h"
# include "./minishell/cleanup.h"
# include "./minishell/e_builtins.h"
# include "./minishell/e_command.h"
# include "./minishell/e_external.h"
# include "./minishell/e_heredoc.h"
# include "./minishell/e_multiple.h"
# include "./minishell/error.h"
# include "./minishell/executer.h"
# include "./minishell/main.h"
# include "./minishell/parser.h"
# include "./minishell/signal.h"
# include "./minishell/e_redirections.h"

extern int	g_sigint_received;

void sigpipe_handler(int sig);

void	print_shell_info(t_shell *shell);


#endif

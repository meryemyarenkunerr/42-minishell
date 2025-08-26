/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 12:22:50 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTER_H
#define MINISHELL_EXECUTER_H

#include "../structs.h"

/* EXECUTER */
/* executer.c */
void	executer(t_shell *shell);

/* single_command.c */
void	execute_single_command(t_shell *shell, t_command *cmd);

/* utils.c */
int		ft_strcmp(const char *s1, const char *s2);
int		open_output_file(t_shell *shell, t_command *cmd, int i);
void	close_old_fd(int *fd_out);
int		is_input_file(t_command *cmd, char *filename);
int		is_output_file(t_command *cmd, char *filename);

/* utils2.c */
int		setup_single_input_file(t_shell *shell, t_command *cmd,
	char *filename);
int		setup_single_output_file(t_shell *shell, t_command *cmd,
	char *filename, int append_mode);

#endif // MINISHELL_EXECUTER_H

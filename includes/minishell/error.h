/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:29:55 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:29:56 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../structs.h"

void	not_valid_identifier(char *type, char *arg);
void	no_such_file_or_directory(char *command);
void	too_many_argument_error_exit(t_shell *shell, t_command *cmd);
void	numeric_argument_error_exit(t_shell *shell, t_command *cmd);
void	ft_exit(t_shell *shell, t_command *cmd);
void	handle_execve_error(char *cmd);
void	command_not_found_error(t_shell *shell, char *cmd);
void	print_eof_warning(char *delimiter);
void	pipes_creation_error(t_shell *shell);
void	print_file_error(char *filename, char *error_msg);
void	quote_error(void);
void	redirects_error(char *text, t_shell *shell);

#endif

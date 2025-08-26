/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 12:22:50 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEREDOC_H
#define MINISHELL_HEREDOC_H

#include "../structs.h"

/* EXECUTER/HEREDOC */
/* heredoc_child.c */
void	process_single_heredoc_ignore(t_shell *shell, char *delimiter,
			int fds[2]);
void	process_single_heredoc(t_shell *shell, char *delimiter,
			int fds[2]);
void	handle_heredoc_input(t_shell *shell, t_command *cmd, int fds[2]);

/* heredoc_handler.c */
int		setup_heredoc_fds(t_shell *shell, t_command *cmd);

/* heredoc_parent.c */
void	execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid);

/* heredoc_safe_readline.c */
char	*safe_readline(const char *prompt, t_shell *shell, char *content, int fds[2]);

/* heredoc_utils.c */
int		is_heredoc_interrupted(void);
int		check_line_conditions(char *line, char *delimiter);
char	*process_line_content(t_shell *shell, char *line);
void	write_processed_line(int write_fd, char *processed_line);

/* redirections.c */
int		setup_command_fds(t_shell *shell, t_command *cmd);
int		setup_file_descriptors(t_shell *shell);

#endif // MINISHELL_HEREDOC_H

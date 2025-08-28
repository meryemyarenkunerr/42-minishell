/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_heredoc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:29:38 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:29:41 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_HEREDOC_H
# define E_HEREDOC_H

# include "../structs.h"

int		setup_heredoc_fds(t_shell *shell, t_command *cmd);
int		is_heredoc_interrupted(void);
void	process_single_heredoc(t_shell *shell, char *delimiter, int fds[2]);
void	process_single_heredoc_ignore(t_shell *shell, char *delimiter,
			int fds[2]);
char	*read_line(const char *prompt, t_shell *shell, char *content,
			int fds[2]);
int		handle_wait_status(int status, t_shell *shell);

#endif

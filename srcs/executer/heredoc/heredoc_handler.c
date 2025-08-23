/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	setup_heredoc_fds(t_shell *shell, t_command *cmd)
{
	int		pipe_fds[2];
	pid_t	pid = 0;

	if (!cmd || cmd->heredoc_count == 0)
		return (TRUE);
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (FALSE);
	}
	handle_heredoc_input(shell, cmd, pipe_fds);
	execute_heredoc_parent(cmd, pipe_fds, pid);
	return (TRUE);
}

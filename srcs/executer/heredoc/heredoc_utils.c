/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:33:45 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:33:47 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_heredoc_interrupted(void)
{
	if (g_sigint_received == IN_HEREDOC)
		return (FALSE);
	else
		return (TRUE);
}

int	handle_wait_status(int status, t_shell *shell)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_sigint_received = AFTER_HEREDOC;
		shell->exit_status = 130;
		handle_signals();
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_sigint_received = AFTER_HEREDOC;
		shell->exit_status = 130;
		handle_signals();
		return (1);
	}
	return (0);
}

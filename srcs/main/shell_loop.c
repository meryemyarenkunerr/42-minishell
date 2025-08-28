/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:32:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:32:29 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_exit(t_shell *shell)
{
	char	*cmd;
	char	*prompt;

	prompt = build_prompt();
	cmd = readline(prompt);
	free(prompt);
	if (!cmd)
		return (TRUE);
	if (ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (FALSE);
	}
	if (*cmd && ft_strlen(cmd) > 0)
		add_history(cmd);
	process_command(shell, cmd);
	return (FALSE);
}

void	shell_loop(t_shell *shell)
{
	if (!shell || !shell->environment)
	{
		shell->exit_status = 1;
		return ;
	}
	while (!shell->exit)
	{
		if (is_exit(shell))
			break ;
	}
	rl_clear_history();
}

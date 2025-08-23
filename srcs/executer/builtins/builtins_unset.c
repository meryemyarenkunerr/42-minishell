/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_flag_unset(t_shell *shell, char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-')
			count++;
		if (count > 2)
		{
			write(STDERR_FILENO, "minishell: unset: --: invalid option\n", 37);
			shell->exit_status = 2;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	execute_builtin_unset(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd->arguments[1])
	{
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	if (!is_valid_flag_unset(shell, cmd->arguments[i]))
		return ;
	while (cmd->arguments[i])
	{
		remove_env_variable(&shell->environment, cmd->arguments[i]);
		i++;
	}
	if (shell->exit_status != 1)
		shell->exit_status = 0;
}

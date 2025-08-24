/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_dollar_question_mark(t_shell *shell, const char *arg)
{
	if (!ft_strcmp(arg, "$?"))
	{
		printf("%d", shell->exit_status);
		return (TRUE);
	}
	return (FALSE);
}

int	is_valid_echo_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (FALSE);
	if (arg[1] == '\0')
		return (FALSE);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	execute_builtin_echo(t_shell *shell, t_command *cmd)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 1;
	while (cmd->arguments[i] && is_valid_echo_flag(cmd->arguments[i]))
	{
		nl_flag = 0;
		i++;
	}
	while (cmd->arguments[i])
	{
		if (!is_dollar_question_mark(shell, cmd->arguments[i]))
			printf("%s", cmd->arguments[i]);
		if (cmd->arguments[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
	shell->exit_status = 0;
}

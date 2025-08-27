/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:37:44 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_dollar_question_mark(t_shell *shell, const char *arg)
{
	if (!ft_strcmp(arg, "$?"))
	{
		printf("%d", shell->exit_status);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_valid_echo_flag(const char *arg)
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
			ft_putstr_fd(cmd->arguments[i], STDOUT_FILENO);
		if (cmd->arguments[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	shell->exit_status = 0;
}

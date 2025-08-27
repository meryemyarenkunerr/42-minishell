/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:42:43 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	setup_builtin_redirections(t_command *cmd, int saved_fds[2])
{
	saved_fds[0] = -1;
	saved_fds[1] = -1;
	if (cmd->fd_in != STDIN_FILENO)
	{
		saved_fds[0] = dup(STDIN_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		saved_fds[1] = dup(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

static void	restore_builtin_redirections(int saved_fds[2])
{
	if (saved_fds[0] != -1)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
	}
	if (saved_fds[1] != -1)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
	}
}

int	is_builtin_command(const char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, CD) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, ECHO_) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, ENV) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, EXPORT) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, PWD) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, UNSET) == 0)
		return (TRUE);
	if (ft_strcmp(cmd, EXIT) == 0)
		return (TRUE);
	return (FALSE);
}

void	call_builtin_function(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, CD) == 0)
		execute_builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->cmd, ECHO_) == 0)
		execute_builtin_echo(shell, cmd);
	else if (ft_strcmp(cmd->cmd, ENV) == 0)
		execute_builtin_env(shell, cmd);
	else if (ft_strcmp(cmd->cmd, EXPORT) == 0)
		execute_builtin_export(shell, cmd);
	else if (ft_strcmp(cmd->cmd, PWD) == 0)
		execute_builtin_pwd(shell, cmd);
	else if (ft_strcmp(cmd->cmd, UNSET) == 0)
		execute_builtin_unset(shell, cmd);
	else if (ft_strcmp(cmd->cmd, EXIT) == 0)
		execute_builtin_exit(shell, cmd);
}

void	execute_builtin(t_shell *shell, t_command *cmd)
{
	int	saved_fds[2];

	setup_builtin_redirections(cmd, saved_fds);
	call_builtin_function(shell, cmd);
	restore_builtin_redirections(saved_fds);
}

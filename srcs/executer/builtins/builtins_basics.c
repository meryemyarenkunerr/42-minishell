/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 04:02:30 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	env_node_printer(t_env *env_node)
{
	ft_putstr_fd(env_node->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(env_node->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	execute_builtin_env(t_shell *shell, t_command *cmd)
{
	t_env	*curr;

	(void)cmd;
	if (!shell->environment)
	{
		shell->exit_status = 0;
		return ;
	}
	if (cmd->arguments[1])
	{
		no_such_file_or_directory(cmd->cmd);
		shell->exit_status = 127;
		return ;
	}
	curr = shell->environment;
	while (curr)
	{
		if (curr->key && ft_strlen(curr->value) > 0)
			env_node_printer(curr);
		curr = curr->next;
	}
	shell->exit_status = 0;
}

void	execute_builtin_pwd(t_shell *shell, t_command *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	shell->exit_status = 0;
}

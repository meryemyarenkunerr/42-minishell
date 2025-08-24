/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/24 16:02:06 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, ft_strlen(cmd->cmd));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		shell->exit_status = 127;
		return ;
	}
	curr = shell->environment;
	while (curr)
	{
		if (curr->key && ft_strlen(curr->value) > 0)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	shell->exit_status = 0;
}

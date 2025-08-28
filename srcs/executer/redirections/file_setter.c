/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_setter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:32:53 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:32:54 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	setup_single_input_file(t_shell *shell, t_command *cmd, char *filename)
{
	int	fd;

	if (!filename)
		return (FALSE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_file_error(filename, "No such file or directory");
		shell->exit_status = 1;
		return (FALSE);
	}
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in > STDERR_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (TRUE);
}

int	setup_single_output_file(t_shell *shell, t_command *cmd,
	char *filename, int append_mode)
{
	int	fd;
	int	flags;

	if (!filename)
		return (FALSE);
	if (append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		print_file_error(filename, "Permission denied");
		shell->exit_status = 1;
		return (FALSE);
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out > STDERR_FILENO)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:35:22 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_heredoc_interrupted(void)
{
	return (g_sigint_received == SIGINT);
}

int	check_line_conditions(char *line, char *delimiter)
{
	if (is_heredoc_interrupted())
	{
		if (line)
			free(line);
		return (1);
	}
	if (!line)
	{
		print_eof_warning(delimiter);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

char	*process_line_content(t_shell *shell, char *line)
{
	if (shell->commands->quote_flag == 1)
		return (line);
	else
		return (expand_variable(line, shell));
}

void	write_processed_line(int write_fd, char *processed_line)
{
	write(write_fd, processed_line, ft_strlen(processed_line));
	write(write_fd, "\n", 1);
}

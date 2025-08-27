/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 00:29:06 by iaktas           ###   ########.fr       */
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

int	check_line_conditions(char *line, char *delimiter)
{
	if (!line)
	{
		if (errno == SIGQUIT)
			print_eof_warning(delimiter);
		g_sigint_received = AFTER_HEREDOC;
		handle_signals();
		return (1);
	}
	if (is_heredoc_interrupted())
	{
		if (line)
			free(line);
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
}

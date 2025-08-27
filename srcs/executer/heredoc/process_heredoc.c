/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 15:31:37 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*heredoc_join_line(char *content, char *line)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(content, line);
	free(content);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	joined = ft_strjoin(tmp, "\n");
	free(tmp);
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (!joined)
		return (NULL);
	return (joined);
}

static char	*process_line_content(t_shell *shell, char *line)
{
	if (shell->commands->quote_flag == 1)
		return (line);
	else
		return (expand_variable(line, shell));
}

static int	check_line_conditions(char *line, char *delimiter)
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

void	process_single_heredoc(t_shell *shell, char *delimiter, int fds[2])
{
	char	*line;
	char	*processed_line;
	char	*temp;

	processed_line = ft_strdup("");
	while (!is_heredoc_interrupted())
	{
		line = read_line(BLUE PROMPT_HEREDOC RESET,
				shell, processed_line, fds);
		if (check_line_conditions(line, delimiter))
			break ;
		temp = process_line_content(shell, ft_strdup(line));
		processed_line = heredoc_join_line(processed_line, temp);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (!is_heredoc_interrupted())
		write(fds[1], processed_line, ft_strlen(processed_line));
	if (processed_line)
		free(processed_line);
}

void	process_single_heredoc_ignore(t_shell *shell, char *delimiter,
	int fds[2])
{
	char	*line;

	while (!is_heredoc_interrupted())
	{
		line = read_line(BLUE PROMPT_HEREDOC RESET, shell, NULL, fds);
		if (!line)
			break ;
		if (is_heredoc_interrupted())
		{
			if (line)
				free(line);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

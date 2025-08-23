#include "../../../includes/minishell.h"

void	process_single_heredoc_ignore(t_shell *shell, char *delimiter, int fds[2])
{
	char	*line;

	while (!is_heredoc_interrupted())
	{
		line = safe_readline(BLUE PROMPT_HEREDOC RESET, shell, NULL, fds);
		if (!line)
		{
			print_eof_warning(delimiter);
			g_sigint_received = AFTER_HEREDOC;
			handle_signals();
			break ;
		}
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
	free(line);
	if (!joined)
		return (NULL);
	return (joined);
}

void	process_single_heredoc(t_shell *shell, char *delimiter, int fds[2])
{
	char	*line;
	char	*processed_line;
	char	*temp;

	processed_line = ft_strdup("");
	while (!is_heredoc_interrupted())
	{
		line = safe_readline(BLUE PROMPT_HEREDOC RESET, shell, processed_line, fds);
		if (check_line_conditions(line, delimiter))
			break ;
		temp = process_line_content(shell, line);
		processed_line = heredoc_join_line(processed_line, temp);
		free(line);
	}
	if (!is_heredoc_interrupted())
		write_processed_line(fds[1], processed_line);
	if (processed_line)
		free(processed_line);
}

void	handle_heredoc_input(t_shell *shell, t_command *cmd, int fds[2])
{
	int	i;

	i = 0;
	g_sigint_received = IN_HEREDOC;
	handle_signals();
	while (i < cmd->heredoc_count && !is_heredoc_interrupted())
	{
		if (i == cmd->heredoc_count - 1)
			process_single_heredoc(shell, cmd->heredoc_delimiter[i], fds);
		else
			process_single_heredoc_ignore(shell, cmd->heredoc_delimiter[i], fds);
		i++;
	}
	g_sigint_received = AFTER_HEREDOC;
	handle_signals();
	close(fds[1]);
}

// void	execute_heredoc_child(t_shell *shell, t_command *cmd, int fds[2])
// {

// 	// setup_heredoc_signals();

// // 	rl_clear_history();
// 	// restore_heredoc_signals();
// // 	close(fds[0]);
// /* 	if (is_heredoc_interrupted())
// 		complete_cleanup_and_exit(shell, 130);
// 	else
// 		complete_cleanup_and_exit(shell, 0); */
// }

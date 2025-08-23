#include "../../../includes/minishell.h"

void	process_single_heredoc_ignore(char *delimiter, int write_fd)
{
	char	*line;

	(void)write_fd;
	while (!is_heredoc_interrupted())
	{
		line = readline(BLUE PROMPT_HEREDOC RESET);
		if (is_heredoc_interrupted())
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
		{
			print_eof_warning(delimiter);
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

void	process_single_heredoc(t_shell *shell, char *delimiter, int write_fd)
{
	char	*line;
	char	*processed_line;

	while (!is_heredoc_interrupted())
	{
		line = readline(BLUE PROMPT_HEREDOC RESET);
		if (check_line_conditions(line, delimiter))
			break ;
		processed_line = process_line_content(shell, line);
		write_processed_line(write_fd, processed_line);
		if (shell->commands->quote_flag != 1)
			free(processed_line);
		free(line);
	}
}

void	handle_heredoc_input(t_shell *shell, t_command *cmd, int write_fd)
{
	int	i;

	i = 0;
	while (i < cmd->heredoc_count && !is_heredoc_interrupted())
	{
		if (i == cmd->heredoc_count - 1)
			process_single_heredoc(shell, cmd->heredoc_delimiter[i], write_fd);
		else
			process_single_heredoc_ignore(cmd->heredoc_delimiter[i], write_fd);
		i++;
	}
	close(write_fd);
}

void	execute_heredoc_child(t_shell *shell, t_command *cmd, int fds[2])
{
	close(fds[0]);
	setup_heredoc_signals();
	handle_heredoc_input(shell, cmd, fds[1]);
	rl_clear_history();
	restore_heredoc_signals();
	if (is_heredoc_interrupted())
		complete_cleanup_and_exit(shell, 130);
	else
		complete_cleanup_and_exit(shell, 0);
}

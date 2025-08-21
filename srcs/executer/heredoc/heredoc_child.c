#include "../../../includes/minishell.h"

void	process_single_heredoc_ignore(char *delimiter, int write_fd)
{
	char	*line;

	(void)write_fd;
	while (1)
	{
		line = readline(BLUE PROMPT_HEREDOC RESET);
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

	processed_line = NULL;
	while (1)
	{
		line = readline(BLUE PROMPT_HEREDOC RESET);
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
		if (shell->commands->quote_flag == 1)
			processed_line = line;
		else
			processed_line = expand_variable(line, shell);
		write(write_fd, processed_line, ft_strlen(processed_line));
		write(write_fd, "\n", 1);
		if (shell->commands->quote_flag != 1)
			free(processed_line);
		free(line);
	}
}

void	handle_heredoc_input(t_shell *shell, t_command *cmd, int write_fd)
{
	int	i;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (i == cmd->heredoc_count - 1)
			process_single_heredoc(shell, cmd->heredoc_delimiter[i], write_fd);
		else
			process_single_heredoc_ignore(cmd->heredoc_delimiter[i], write_fd);
		i++;
	}
	close(write_fd);
	rl_clear_history();
	exit(0);
}

void	execute_heredoc_child(t_shell *shell, t_command *cmd, int fds[2])
{
	close(fds[0]);
	handle_heredoc_input(shell, cmd, fds[1]);
	exit(0);
}

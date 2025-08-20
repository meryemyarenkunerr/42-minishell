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
			write(STDERR_FILENO, "\nminishell: warning: here-document delimited by ", 48);
			write(STDERR_FILENO, "end-of-file (wanted `", 21);
			write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
			write(STDERR_FILENO, "')\n", 3);
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

void	process_single_heredoc(char *delimiter, int write_fd)
{
	char	*line;

	(void)write_fd;
	while (1)
	{
		line = readline(BLUE PROMPT_HEREDOC RESET);
		if (!line)
		{
			write(STDERR_FILENO, "\nminishell: warning: here-document delimited by ", 48);
			write(STDERR_FILENO, "end-of-file (wanted `", 21);
			write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
			write(STDERR_FILENO, "')\n", 3);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc_input(t_command *cmd, int write_fd)
{
	int	i;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (i == cmd->heredoc_count - 1)
			process_single_heredoc(cmd->heredoc_delimiter[i], write_fd);
		else
			process_single_heredoc_ignore(cmd->heredoc_delimiter[i], write_fd);
		i++;
	}
	close(write_fd);
	rl_clear_history();
	exit(0);
}

void	execute_heredoc_child(t_command *cmd, int fds[2])
{
	close(fds[0]);
	handle_heredoc_input(cmd, fds[1]);
	exit(0);
}

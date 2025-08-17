#include "../../../includes/minishell.h"

void	process_single_heredoc(char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT_HEREDOC);
		if (!line)
		{
			printf("\nminishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
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
		process_single_heredoc(cmd->heredoc_delimiter[i], write_fd);
		i++;
	}
	close(write_fd);
	rl_clear_history();
	exit(0);	// bu kısım düzenlenecek
}

void	execute_heredoc_child(t_command *cmd, int fds[2])
{
	close(fds[0]); // read end'i kapat
	handle_heredoc_input(cmd, fds[1]); // input al
	exit(0); // chil process'i sonlandır
}
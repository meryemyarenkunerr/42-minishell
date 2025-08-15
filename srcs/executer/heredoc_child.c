#include "../../includes/minishell.h"

static void	write_heredoc_to_pipe(int write_fd, const char *delimeter)
{
	char	*line;

	g_sigint_received = 0; // yeni eklendi
	while (1)
	{
		printf("DEBUG: Child - before readline\n");
		line = readline(PROMPT_HEREDOC);
		printf("DEBUG: Child - after readline, line = '%s'\n", line ? line : "NULL");
		if (!line) // Ctrl+D gelirse
		{
			printf("DEBUG: Ctrl+D detected, breaking\n");
			break ;
		}
		if (g_sigint_received) // Ctrl+C geldiyse
		{
			printf("DEBUG: Child - g_sigint_received = 1\n");
			free(line);
			g_sigint_received = 0;
			break ;
		}
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	printf("DEBUG: Exiting write_heredoc_to_pipe\n");
}

void	heredoc_child_process(int fds[2], const char *delimeter)
{
	signal(SIGINT, SIG_DFL);
	close(fds[0]); // read end'i kapat
	write_heredoc_to_pipe(fds[1], delimeter);
	close(fds[1]);
	exit(0); // child process'i sonlandırmak için
}

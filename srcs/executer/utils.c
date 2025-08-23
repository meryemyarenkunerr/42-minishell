#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
int	open_output_file(t_shell *shell, t_command *cmd, int i)
{
	int	flags;
	int	fd;

	flags = (cmd->append_modes && cmd->append_modes[i])
		? O_WRONLY | O_CREAT | O_APPEND
		: O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(cmd->output_files[i], flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_files[i]);
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

void	close_old_fd(int *fd_out)
{
	if (*fd_out != STDOUT_FILENO && *fd_out != -1)
		close(*fd_out);
}

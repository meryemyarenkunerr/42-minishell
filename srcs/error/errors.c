#include "../../includes/minishell.h"

void	handle_export_error(t_shell *shell, const char *arg)
{
	printf("export `%s': not a valid identifier\n", arg);
	shell->exit_status = 1;
}

int	fork_error_handler(int fds[2], t_shell *shell)
{
	perror("fork");
	close(fds[0]);
	close(fds[1]);
	signal(SIGINT, handle_sigint); // restore
	shell->exit_status = 1;
	return FALSE;
}
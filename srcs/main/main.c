#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	shell_loop(&shell);
	free_at_exit(&shell);
	return (shell.exit_status);
}
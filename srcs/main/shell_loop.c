#include "../../includes/minishell.h"

int	is_exit(t_shell *shell)
{
	char	*cmd;
	char	*prompt;

	prompt = build_prompt();
	cmd =readline(prompt);
	free(prompt);
	if (!cmd)
	{
		//printf("bye bye <3\n");
		return (TRUE);
	}
	if (ft_strlen(cmd) == 0)
		return (FALSE);
	if (*cmd && ft_strlen(cmd) > 0)
		add_history(cmd);
	process_command(shell, cmd);
	// free(cmd);
	return (FALSE);
}

void	shell_loop(t_shell *shell)
{
	if (!shell || !shell->environment)
	{
		shell->exit_status = 1;
		return ;
	}
	while (!shell->exit)
	{
		if (is_exit(shell))
			break ;
	}
	rl_clear_history();
}

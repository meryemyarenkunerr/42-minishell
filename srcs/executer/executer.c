#include "../../includes/minishell.h"

static int	has_pipeline(t_shell *shell)
{
	return (shell->pipeline && shell->pipeline->count > 1);
}

void	executer(t_shell *shell)
{
	// t_command içini doldurma (input/output file ve append_mode)
	if (!filler_commands(shell))
	{
		shell->exit_status = 1;
		return ;
	}
	if (!handle_heredocs(shell))
	{
		shell->exit_status = 1;
		return ;
	}
	if (has_pipeline(shell))
		execute_pipeline(shell);
	else
		execute_single_command(shell);
}


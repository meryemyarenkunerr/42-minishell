#include "../../includes/minishell.h"

void	complete_cleanup_and_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	restore_heredoc_signals();
	free_at_exit(shell);
	exit(exit_code);
}

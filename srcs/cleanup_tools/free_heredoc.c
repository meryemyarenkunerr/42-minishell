#include "../../includes/minishell.h"

void	complete_cleanup_and_exit(t_shell *shell, int exit_code)
{
	// Readline cleanup
	rl_clear_history();

	// Sinyal handler restore
	restore_heredoc_signals();

	// Shell memory cleanup
	free_at_exit(shell);

	// Exit
	exit(exit_code);
}
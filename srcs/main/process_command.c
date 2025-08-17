#include "../../includes/minishell.h"

void	process_command(t_shell *shell, char *command)
{
	if (!shell || !command)
		return ;

	cleanup_previous_state(shell);

	// parser&lexer ile t_pipeline gelecek

	// t_command içini doldurma (input/output file, heredoc, append mode)
	shell->pipeline = mock_cat_double_heredoc();
	if (!builds_commands_from_pipeline(shell))
		return ;
	// redirection ve heredoc
	if (!setup_file_descriptors(shell))
		return ;
	printf("\n================= BEFORE =================\n");
	print_shell_info(shell);
	printf("\n================= AFTER ==================\n");
	executer(shell);
	print_shell_info(shell);
}
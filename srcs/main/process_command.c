#include "../../includes/minishell.h"

void	process_command(t_shell *shell, char *command)
{
	if (!shell || !command)
		return ;
	cleanup_previous_state(shell);
	shell->pipeline = process_input(command, shell);
	// print_shell_info(shell);
	free(command);
	if (!shell->pipeline)
		return ;
	if (!builds_commands_from_pipeline(shell))
		return ;
	setup_file_descriptors(shell);

	executer(shell);
}

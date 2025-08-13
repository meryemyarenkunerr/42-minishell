#include "../includes/minishell.h"

t_command *create_command_export_multiple_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("export");
	cmd->arguments = create_args_temp(4, (char *[]){"export", "VAR1=test1", "VAR2=test2", "VAR3"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

void fill_shell_export_multiple_temp(t_shell *shell)
{
	shell->commands = create_command_export_multiple_temp();
}
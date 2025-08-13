#include "../includes/minishell.h"

// CD HOME komutu için test mock
t_command *create_command_cd_home_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("cd");
	cmd->arguments = create_args_temp(1, (char *[]){"cd"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

t_pipeline *create_pipeline_cd_home_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Tek token: "cd"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("cd");
	t1->type = TOKEN_COMMAND;
	t1->prev = NULL;
	t1->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

void fill_shell_cd_home_temp(t_shell *shell)
{
	shell->commands = create_command_cd_home_temp();
	shell->pipeline = create_pipeline_cd_home_temp();
}
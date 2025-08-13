#include "../includes/minishell.h"

// UNSET komutu için test mock - tek variable
t_command *create_command_unset_single_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("unset");
	// unset USER
	cmd->arguments = create_args_temp(2, (char *[]){"unset", "USER"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

t_pipeline *create_pipeline_unset_single_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Token 1: "unset"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("unset");
	t1->type = TOKEN_COMMAND;
	t1->prev = NULL;

	// Token 2: "USER"
	t_token *t2 = malloc(sizeof(t_token));
	t2->content = strdup("USER");
	t2->type = TOKEN_WORD;
	t2->prev = t1;
	t1->next = t2;
	t2->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

void fill_shell_unset_single_temp(t_shell *shell)
{
	shell->commands = create_command_unset_single_temp();
	shell->pipeline = create_pipeline_unset_single_temp();
}

// UNSET komutu için test mock - multiple variables
t_command *create_command_unset_multiple_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("unset");
	// unset USER PATH HOME
	cmd->arguments = create_args_temp(4, (char *[]){"unset", "USER", "PATH", "HOME"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

void fill_shell_unset_multiple_temp(t_shell *shell)
{
	shell->commands = create_command_unset_multiple_temp();
	// Pipeline basit olduğu için atlıyorum
}
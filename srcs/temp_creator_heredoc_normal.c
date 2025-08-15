#include "../includes/minishell.h"

// Heredoc normal test için mock
t_command *create_command_heredoc_normal_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("cat");
	cmd->arguments = create_args_temp(1, (char *[]){"cat"});
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_count = 1;
	cmd->heredoc_delimeter = malloc(sizeof(char*) * 2);
	cmd->heredoc_delimeter[0] = strdup("EOF");
	cmd->heredoc_delimeter[1] = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

t_pipeline *create_pipeline_heredoc_normal_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Token 1: "cat"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("cat");
	t1->type = TOKEN_COMMAND;
	t1->prev = NULL;
	t1->next = NULL;

	pipeline->token_lists[0] = t1;
	return pipeline;
}

void fill_shell_heredoc_normal_temp(t_shell *shell)
{
	shell->commands = create_command_heredoc_normal_temp();
	shell->pipeline = create_pipeline_heredoc_normal_temp();
}
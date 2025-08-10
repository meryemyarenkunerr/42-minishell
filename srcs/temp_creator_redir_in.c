#include "../includes/minishell.h"

t_command *create_command_cat_input_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd) return NULL;

	cmd->cmd = strdup("cat");

	cmd->arguments = create_args_temp(3, (char *[]){"cat", "<", "input.txt"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

t_pipeline *create_pipeline_cat_input_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline) return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("cat");
	t1->type = TOKEN_WORD;
	t1->prev = NULL;

	t_token *t2 = malloc(sizeof(t_token));
	t2->content = strdup("<");
	t2->type = TOKEN_REDIRECT_IN;
	t2->prev = t1;
	t1->next = t2;

	t_token *t3 = malloc(sizeof(t_token));
	t3->content = strdup("input.txt");
	t3->type = TOKEN_WORD;
	t3->prev = t2;
	t2->next = t3;
	t3->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

void fill_shell_cat_input_temp(t_shell *shell)
{
	t_command *cmd1 = create_command_cat_input_temp();

	shell->commands = cmd1;
	shell->pipeline = create_pipeline_cat_input_temp();
}

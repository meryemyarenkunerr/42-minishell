#include "../includes/minishell.h"

// ECHO -n komutu için test mock
t_command *create_command_echo_n_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("echo");

	// echo -n hello
	cmd->arguments = create_args_temp(3, (char *[]){"echo", "-n", "hello"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

// Echo -n için pipeline
t_pipeline *create_pipeline_echo_n_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Token 1: "echo"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("echo");
	t1->type = TOKEN_COMMAND;
	t1->prev = NULL;

	// Token 2: "-n"
	t_token *t2 = malloc(sizeof(t_token));
	t2->content = strdup("-n");
	t2->type = TOKEN_WORD;
	t2->prev = t1;
	t1->next = t2;

	// Token 3: "hello"
	t_token *t3 = malloc(sizeof(t_token));
	t3->content = strdup("hello");
	t3->type = TOKEN_WORD;
	t3->prev = t2;
	t2->next = t3;
	t3->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

// Shell yapısını echo -n komutu ile doldur
void fill_shell_echo_n_temp(t_shell *shell)
{
	t_command *cmd1 = create_command_echo_n_temp();

	shell->commands = cmd1;
	shell->pipeline = create_pipeline_echo_n_temp();
}
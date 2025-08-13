#include "../includes/minishell.h"

// ENV komutu için test mock
t_command *create_command_env_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("env");

	// env'de sadece komut adı var, başka argument yok
	cmd->arguments = create_args_temp(1, (char *[]){"env"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

// ENV için pipeline
t_pipeline *create_pipeline_env_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Tek token: "env"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("env");
	t1->type = TOKEN_COMMAND;
	t1->prev = NULL;
	t1->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

// Shell yapısını env komutu ile doldur
void fill_shell_env_temp(t_shell *shell)
{
	t_command *cmd1 = create_command_env_temp();

	shell->commands = cmd1;
	shell->pipeline = create_pipeline_env_temp();
}
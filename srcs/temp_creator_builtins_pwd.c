#include "../includes/minishell.h"

// PWD komutu için test mock
t_command *create_command_pwd_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;

	cmd->cmd = strdup("pwd");

	// pwd'de sadece komut adı var, başka argument yok
	cmd->arguments = create_args_temp(1, (char *[]){"pwd"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;
	cmd->next = NULL;

	return cmd;
}

// PWD için pipeline (tek komut, redirection yok)
t_pipeline *create_pipeline_pwd_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return NULL;

	pipeline->count = 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// Tek token: "pwd"
	t_token *t1 = malloc(sizeof(t_token));
	t1->content = strdup("pwd");
	t1->type = TOKEN_COMMAND;  // veya TOKEN_WORD
	t1->prev = NULL;
	t1->next = NULL;

	pipeline->token_lists[0] = t1;

	return pipeline;
}

// Shell yapısını pwd komutu ile doldur
void fill_shell_pwd_temp(t_shell *shell)
{
	t_command *cmd1 = create_command_pwd_temp();

	shell->commands = cmd1;
	shell->pipeline = create_pipeline_pwd_temp();
}
#include "../includes/minishell.h"

// t_command geçici doldurma - output redirection test
t_command *create_command_echo_output_temp(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    cmd->cmd = strdup("echo");

    // arguments: echo hello >
    cmd->arguments = create_args_temp(4, (char *[]){"echo", "hello", ">", "out.txt", NULL});

    // output_file set ediliyor
    cmd->input_file = NULL;
    cmd->output_file = NULL;

    cmd->heredoc_count = 0;
    cmd->heredoc_delimeter = NULL;

    cmd->append_mode = 0;  // append değil, overwrite modu
    cmd->next = NULL;

    return cmd;
}

// Pipeline temp - tek komut (echo hello > out.txt)
t_pipeline *create_pipeline_echo_output_temp(void)
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline)
        return NULL;

    pipeline->count = 1;
    pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

    t_token *t1 = malloc(sizeof(t_token));
    t1->content = strdup("echo");
    t1->type = TOKEN_WORD;
    t1->prev = NULL;

    t_token *t2 = malloc(sizeof(t_token));
    t2->content = strdup("hello");
    t2->type = TOKEN_WORD;
    t2->prev = t1;
    t1->next = t2;

    t_token *t3 = malloc(sizeof(t_token));
    t3->content = strdup(">");
    t3->type = TOKEN_REDIRECT_OUT;
    t3->prev = t2;
    t2->next = t3;  // <-- Burada eksikti

    t_token *t4 = malloc(sizeof(t_token));
    t4->content = strdup("out.txt");
    t4->type = TOKEN_WORD;
    t4->prev = t3;
    t3->next = t4;
    t4->next = NULL;

    pipeline->token_lists[0] = t1;

    return pipeline;
}

// Shell doldurma fonksiyonu - output redirection
void fill_shell_echo_output_temp(t_shell *shell)
{
    t_command *cmd = create_command_echo_output_temp();
    shell->commands = cmd;
    shell->pipeline = create_pipeline_echo_output_temp();
}

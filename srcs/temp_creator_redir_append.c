#include "../includes/minishell.h"

// t_command geçici doldurma - append redirection test
t_command *create_command_echo_append_temp(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    cmd->cmd = strdup("echo");
    if (!cmd->cmd)
    {
        free(cmd);
        return NULL;
    }

    cmd->arguments = create_args_temp(4, (char *[]){"echo", "hello", ">>", "out.txt"});
    if (!cmd->arguments)
    {
        free(cmd->cmd);
        free(cmd);
        return NULL;
    }

    cmd->input_file = NULL;
    cmd->output_file = strdup("out.txt");
    if (!cmd->output_file)
    {
        for (int i = 0; cmd->arguments[i]; i++)
            free(cmd->arguments[i]);
        free(cmd->arguments);
        free(cmd->cmd);
        free(cmd);
        return NULL;
    }

    cmd->heredoc_count = 0;
    cmd->heredoc_delimeter = NULL;

    cmd->append_mode = 1;  // Append modu
    cmd->next = NULL;

    return cmd;
}

// Pipeline temp - tek komut (echo hello >> out.txt)
t_pipeline *create_pipeline_echo_append_temp(void)
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    if (!pipeline)
        return NULL;

    pipeline->count = 1;
    pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);
    if (!pipeline->token_lists)
    {
        free(pipeline);
        return NULL;
    }

    t_token *t1 = malloc(sizeof(t_token));
    t_token *t2 = malloc(sizeof(t_token));
    t_token *t3 = malloc(sizeof(t_token));
    t_token *t4 = malloc(sizeof(t_token));
    if (!t1 || !t2 || !t3 || !t4)
    {
        free(t1); free(t2); free(t3); free(t4); free(pipeline);
        return NULL;
    }

    t1->content = strdup("echo");
    t1->type = TOKEN_WORD;
    t1->prev = NULL;
    t1->next = t2;

    t2->content = strdup("hello");
    t2->type = TOKEN_WORD;
    t2->prev = t1;
    t2->next = t3;

    t3->content = strdup(">>");
    t3->type = TOKEN_APPEND;
    t3->prev = t2;
    t3->next = t4;

    t4->content = strdup("out.txt");
    t4->type = TOKEN_WORD;
    t4->prev = t3;
    t4->next = NULL;

    pipeline->token_lists[0] = t1;

    return pipeline;
}

// Shell doldurma fonksiyonu - append redirection
void fill_shell_echo_append_temp(t_shell *shell)
{
    t_command *cmd = create_command_echo_append_temp();
    shell->commands = cmd;
    shell->pipeline = create_pipeline_echo_append_temp();
}

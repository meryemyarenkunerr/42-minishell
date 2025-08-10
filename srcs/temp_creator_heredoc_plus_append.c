#include "../includes/minishell.h"

t_command *create_command_heredoc_append_temp(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    cmd->cmd = strdup("echo");
    // arguments içinde komut + heredoc + append hepsi var
    cmd->arguments = create_args_temp(6, (char *[]){"echo", "hello", ">>", "out.txt", "<<", "EOF1", NULL});
    // Yukarıdaki örnek komut biraz kısaltıldı, 6 argüman yerine 7 olabilir. Burayı ihtiyaca göre artırabilirsin.

    cmd->input_file = NULL;
    cmd->output_file = NULL;

    cmd->heredoc_count = 0;

    // heredoc delimiter dizisi malloc ve doldurma
    cmd->heredoc_delimeter = NULL;

    cmd->append_mode = 1;  // append modu

    cmd->next = NULL;

    return cmd;
}

t_pipeline *create_pipeline_heredoc_append_temp(void)
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
    t_token *t5 = malloc(sizeof(t_token));
    t_token *t6 = malloc(sizeof(t_token));
    if (!t1 || !t2 || !t3 || !t4 || !t5 || !t6)
    {
        free(t1); free(t2); free(t3); free(t4); free(t5); free(t6);
        free(pipeline->token_lists);
        free(pipeline);
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
    t4->next = t5;

    t5->content = strdup("<<");
    t5->type = TOKEN_HEREDOC;
    t5->prev = t4;
    t5->next = t6;

    t6->content = strdup("EOF1");
    t6->type = TOKEN_WORD;
    t6->prev = t5;
    t6->next = NULL;

    pipeline->token_lists[0] = t1;

    return pipeline;
}

void fill_shell_heredoc_append_temp(t_shell *shell)
{
    t_command *cmd = create_command_heredoc_append_temp();
    shell->commands = cmd;
    shell->pipeline = create_pipeline_heredoc_append_temp();
}

#include "../includes/minishell.h"

// t_command geçici doldurma - multiple heredocs test
t_command *create_command_multi_heredoc_temp(void)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    cmd->cmd = strdup("cat");
    cmd->arguments = create_args_temp(5, (char *[]){"cat", "<<", "EOF1", "<<", "EOF2", NULL});

    cmd->input_file = NULL;
    cmd->output_file = NULL;

    // kaç tane heredoc olduğunu bilmiyoruz, 0 başlat
    cmd->heredoc_count = 0;

    // delimiter’ları doldurma
    cmd->heredoc_delimeter = NULL;

    cmd->append_mode = 0;
    cmd->next = NULL;

    return cmd;
}

// Pipeline temp - tek komut (cat <<EOF1 <<EOF2)
t_pipeline *create_pipeline_cat_heredocs_temp(void)
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
    if (!t1 || !t2 || !t3 || !t4 || !t5)
    {
        free(t1); free(t2); free(t3); free(t4); free(t5); free(pipeline);
        return NULL;
    }

    t1->content = strdup("cat");
    t1->type = TOKEN_WORD;
    t1->prev = NULL;
    t1->next = t2;

    t2->content = strdup("<<");
    t2->type = TOKEN_HEREDOC;
    t2->prev = t1;
    t2->next = t3;

    t3->content = strdup("EOF1");
    t3->type = TOKEN_WORD;
    t3->prev = t2;
    t3->next = t4;

    t4->content = strdup("<<");
    t4->type = TOKEN_HEREDOC;
    t4->prev = t3;
    t4->next = t5;

    t5->content = strdup("EOF2");
    t5->type = TOKEN_WORD;
    t5->prev = t4;
    t5->next = NULL;

    pipeline->token_lists[0] = t1;

    return pipeline;
}

// Shell doldurma fonksiyonu - multiple heredocs
void fill_shell_cat_heredocs_temp(t_shell *shell)
{
    t_command *cmd = create_command_multi_heredoc_temp();
    shell->commands = cmd;
    shell->pipeline = create_pipeline_cat_heredocs_temp();
}
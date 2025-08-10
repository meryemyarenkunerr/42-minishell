#include "../includes/minishell.h"

// Yardımcı fonksiyonlar
char **create_args_temp(int count, char **args)
{
	char **res = malloc(sizeof(char *) * (count + 1));
    if (!res)
        return NULL;

    for (int i = 0; i < count; i++)
    {
        res[i] = strdup(args[i]);
        if (!res[i])
        {
            // strdup başarısızsa öncekileri temizle
            for (int j = 0; j < i; j++)
                free(res[j]);
            free(res);
            return NULL;
        }
    }
    res[count] = NULL;
    return res;
}

// t_command geçici doldurma
t_command *create_command_cat_heredoc_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd) return NULL;

	cmd->cmd = strdup("cat");

	cmd->arguments = create_args_temp(3, (char *[]){"cat", "<<", "EOF", NULL });

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;

	cmd->next = NULL;

	return cmd;
}

t_command *create_command_wc_l_temp(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd) return NULL;

	cmd->cmd = strdup("wc");

	cmd->arguments = create_args_temp(2, (char *[]){"wc", "-l"});

	cmd->input_file = NULL;
	cmd->output_file = NULL;

	cmd->heredoc_count = 0;
	cmd->heredoc_delimeter = NULL;

	cmd->append_mode = 0;

	cmd->next = NULL;

	return cmd;
}

// t_pipeline geçici doldurma
t_pipeline *create_pipeline_cat_wc_temp(void)
{
	t_pipeline *pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline) return NULL;

	pipeline->count = 2;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);

	// İlk token list: cat << EOF
	t_token *head1 = malloc(sizeof(t_token));
	head1->content = strdup("cat");
	head1->type = TOKEN_WORD;
	head1->prev = NULL;

	t_token *redir = malloc(sizeof(t_token));
	redir->content = strdup("<<");
	redir->type = TOKEN_HEREDOC;
	redir->prev = head1;
	head1->next = redir;

	t_token *delim = malloc(sizeof(t_token));
	delim->content = strdup("EOF");
	delim->type = TOKEN_WORD;
	delim->prev = redir;
	redir->next = delim;
	delim->next = NULL;

	pipeline->token_lists[0] = head1;

	// İkinci token list: wc -l
	t_token *head2 = malloc(sizeof(t_token));
	head2->content = strdup("wc");
	head2->type = TOKEN_WORD;
	head2->prev = NULL;

	t_token *arg1 = malloc(sizeof(t_token));
	arg1->content = strdup("-l");
	arg1->type = TOKEN_WORD;
	arg1->prev = head2;
	head2->next = arg1;
	arg1->next = NULL;

	pipeline->token_lists[1] = head2;

	return pipeline;
}

// Shell yapısını dolduran fonksiyon
void fill_shell_commands_and_pipeline_temp(t_shell *shell)
{
	// Komutları oluşturup bağlayalım
	t_command *cmd1 = create_command_cat_heredoc_temp();
	t_command *cmd2 = create_command_wc_l_temp();

	cmd1->next = cmd2;

	shell->commands = cmd1;

	// Pipeline oluştur
	shell->pipeline = create_pipeline_cat_wc_temp();
}

void free_arguments_temp(char **args)
{
    if (!args)
        return;
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

void free_heredoc_delimiters_temp(char **heredocs)
{
    if (!heredocs)
        return;
    for (int i = 0; heredocs[i]; i++)
        free(heredocs[i]);
    free(heredocs);
}

void free_command_temp(t_command *cmd)
{
    if (!cmd)
        return;
    free(cmd->cmd);
    free_arguments_temp(cmd->arguments);
    free(cmd->input_file);
    free(cmd->output_file);
    free_heredoc_delimiters_temp(cmd->heredoc_delimeter);
    free_command_temp(cmd->next);
    free(cmd);
}

// pipeline içindeki token dizilerinin ve tokenların serbest bırakılması
void free_pipeline_token_lists_temp(t_pipeline *pipeline)
{
    if (!pipeline || !pipeline->token_lists)
        return;

    for (int i = 0; i < pipeline->count; i++)
    {
        t_token *token = pipeline->token_lists[i];
        while (token)
        {
            t_token *next = token->next;
            free(token->content);
            free(token);
            token = next;
        }
    }
}

void free_pipeline_temp(t_pipeline *pipeline)
{
    if (!pipeline)
        return;
    free_pipeline_token_lists_temp(pipeline);
    free(pipeline->token_lists);
    free(pipeline);
}

void print_shell_info(t_shell *shell)
{
    if (!shell)
    {
        printf("Shell pointer is NULL\n");
        return;
    }

    printf("Shell Commands:\n");
    t_command *cmd = shell->commands;
    int cmd_index = 1;
    while (cmd)
    {
        printf(" Command %d:\n", cmd_index);
        printf("  cmd: %s\n", cmd->cmd ? cmd->cmd : "(null)");
        printf("  arguments:");
        if (cmd->arguments)
        {
            for (int i = 0; cmd->arguments[i]; i++)
                printf(" '%s'", cmd->arguments[i]);
        }
        else
            printf(" (null)");
        printf("\n");

        printf("  input_file: %s\n", cmd->input_file ? cmd->input_file : "(null)");
        printf("  output_file: %s\n", cmd->output_file ? cmd->output_file : "(null)");
        printf("  append_mode: %d\n", cmd->append_mode);

        if (cmd->heredoc_delimeter)
        {
            printf("  heredoc_delimiters:");
            for (int i = 0; i < cmd->heredoc_count; i++)
                printf(" '%s'", cmd->heredoc_delimeter[i]);
            printf("\n");
        }
        else
            printf("  heredoc_delimiters: (null)\n");

        cmd = cmd->next;
        cmd_index++;
    }

    printf("\nShell Pipeline:\n");
    if (!shell->pipeline)
    {
        printf(" Pipeline is NULL\n");
        return;
    }

    for (int i = 0; i < shell->pipeline->count; i++)
    {
        printf(" Pipeline Segment %d tokens:\n", i + 1);
        t_token *token = shell->pipeline->token_lists[i];
        if (!token)
        {
            printf("  (null tokens)\n");
            continue;
        }
        for (int j = 0; token; j++, token = token->next)
        {
            printf("  Token %d: content='%s', type=%d\n", j + 1, token->content, token->type);
        }
    }
}
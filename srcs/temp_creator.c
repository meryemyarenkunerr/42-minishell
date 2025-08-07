#include "../includes/minishell.h"

t_token *create_token_temp(char *content, t_token_types type)
{
    t_token *new = malloc(sizeof(t_token));
    if (!new) return NULL;  // malloc başarısız olursa NULL döndür

    new->content = strdup(content);
    if (!new->content) {    // strdup başarısızsa allocated hafızayı freele
        free(new);
        return NULL;
    }
    new->type = type;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void append_token(t_token **head, t_token *new_token)
{
	t_token *tmp;

	if (!*head)
	{
		*head = new_token;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
}

/* Tokenizer (Statik olarak elle yazılmış hali) */
t_token *build_token_list()
{
	t_token *head = NULL;
	t_token *current = NULL;

	// cat
	head = create_token_temp("cat", TOKEN_WORD);
	current = head;

	// << heredoc başlatıcısı
	current->next = create_token_temp("<<", TOKEN_HEREDOC); // TOKEN_HEREDOC tanımlı olmalı
	if (!current->next)
		return head;
	current->next->prev = current;
	current = current->next;

	// heredoc delimiter
	current->next = create_token_temp("EOF", TOKEN_ARGUMENT);
	if (!current->next)
		return head;
	current->next->prev = current;
	current = current->next;

	// pipe
	current->next = create_token_temp("|", TOKEN_PIPE);
	if (!current->next)
		return head;
	current->next->prev = current;
	current = current->next;

	// wc
	current->next = create_token_temp("wc", TOKEN_WORD);
	if (!current->next)
		return head;
	current->next->prev = current;
	current = current->next;

	// -l
	current->next = create_token_temp("-l", TOKEN_ARGUMENT);
	if (!current->next)
		return head;
	current->next->prev = current;
	current = current->next;

	return head;
}

/* Split tokens by pipes */
t_token *copy_token(const t_token *src)
{
	t_token *copy = malloc(sizeof(t_token));
	if (!copy)
		return NULL;

	copy->content = strdup(src->content);
	copy->type = src->type;
	copy->prev = NULL;
	copy->next = NULL;
	return copy;
}

t_token *copy_token_list(t_token *start, t_token *end_exclusive)
{
	t_token *new_head = NULL;
	t_token *current = NULL;

	while (start && start != end_exclusive)
	{
		t_token *new_token = malloc(sizeof(t_token));
		if (!new_token)
			return NULL;

		new_token->content = strdup(start->content);
		new_token->type = start->type;
		new_token->prev = NULL;
		new_token->next = NULL;

		if (!new_head)
		{
			new_head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			new_token->prev = current;
			current = new_token;
		}

		start = start->next;
	}
	return new_head;
}

t_pipeline *split_pipeline(t_token *tokens)
{
	t_pipeline *result = malloc(sizeof(t_pipeline));
	t_token **lists = malloc(sizeof(t_token *) * 10); // max 10 komut
	int count = 0;

	t_token *start = tokens;
	t_token *current = tokens;

	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			lists[count++] = copy_token_list(start, current);
			start = current->next;
		}
		current = current->next;
	}

	// son parçayı da ekle
	if (start)
		lists[count++] = copy_token_list(start, NULL);

	result->token_lists = lists;
	result->count = count;
	return result;
}

/* Convert token list to command struct */
t_command *build_commands(t_pipeline *pipeline)
{
	t_command *head = NULL;
	t_command *last = NULL;

	for (int i = 0; i < pipeline->count; i++)
	{
		t_token *token = pipeline->token_lists[i];
		int arg_count = 0;

		// argüman sayısını say (komut + argümanlar)
		t_token *tmp = token;
		while (tmp)
		{
			if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_ARGUMENT)
				arg_count++;
			tmp = tmp->next;
		}

		char **args = malloc(sizeof(char *) * (arg_count + 1));
		int j = 0;
		tmp = token;
		while (tmp)
		{
			if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_ARGUMENT)
				args[j++] = strdup(tmp->content);
			tmp = tmp->next;
		}
		args[j] = NULL;

		t_command *cmd = malloc(sizeof(t_command));
		cmd->cmd = strdup(pipeline->token_lists[i]->content); // Komutun kendisi (ilk token)
		cmd->arguments = args;
		cmd->input_file = NULL;
		cmd->output_file = NULL;
		cmd->append_mode = 0;
		cmd->next = NULL;

		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
	}
	return head;
}

/* Print for test */
void print_commands(t_command *cmds)
{
	int i = 1;
	while (cmds)
	{
		printf("Command %d:\n", i++);
		printf("Command Name: %s\n", cmds->cmd);
		for (int j = 0; cmds->arguments[j]; j++)
		{
			printf("  Arg[%d]: %s\n", j, cmds->arguments[j]);
		}
		cmds = cmds->next;
	}
}

void print_tokens(t_token *head)
{
	int i = 0;
	const char *type_names[] = {
		"TOKEN_NONE", "TOKEN_WORD", "TOKEN_COMMAND", "TOKEN_ARGUMENT",
		"TOKEN_FILE", "TOKEN_PIPE", "TOKEN_REDIRECT_IN", "TOKEN_REDIRECT_OUT",
		"TOKEN_APPEND", "TOKEN_HEREDOC"
	};

	printf("Token List:\n");
	while (head)
	{
		printf("  [%d] content = '%s', type = %s\n", i++, head->content, type_names[head->type]);
		head = head->next;
	}
}

void print_pipeline(t_pipeline *pipeline)
{
	printf("Pipeline (%d command%s):\n", pipeline->count, pipeline->count == 1 ? "" : "s");
	for (int i = 0; i < pipeline->count; i++)
	{
		printf(" Command %d tokens:\n", i + 1);
		print_tokens(pipeline->token_lists[i]);
	}
}

void free_token_list_temp(t_token *head)
{
    t_token *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->content);
        // printf("token->content freed\n");
        free(tmp);
        // printf("token freed\n");
    }
}

void free_pipeline_temp(t_pipeline *pipeline)
{
    if (!pipeline)
        return;

    free(pipeline->token_lists);
    // printf("pipeline->token_lists temizlendi\n");
    free(pipeline);
    // printf("pipeline temizlendi\n");
}

void free_commands_temp(t_command *cmd)
{
	t_command *tmp;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;

		// Argümanları boşalt
		if (tmp->arguments)
		{
			for (int i = 0; tmp->arguments[i]; i++)
			{
				free(tmp->arguments[i]);
				// printf("free_commands_list argüman temizleme\n");
			}
			free(tmp->arguments);
		}

		// Eğer input_file/output_file strdup ile atanıyorsa onları da freele:
		if (tmp->input_file)
			free(tmp->input_file);
		if (tmp->output_file)
			free(tmp->output_file);

		free(tmp);
	}
}

void free_token_list(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		// printf("free_token_list\n");
		tmp = token->next;
		free(token->content);
		free(token);
		token = tmp;
	}
}

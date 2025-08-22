#include "../../includes/minishell.h"

static int	is_special_operatoro(t_token_types type)
{
	if (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

char	*check_redirects_strings(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	if (current->type == TOKEN_PIPE)
		return ("|");
	/*if (is_special_operatoro(current->type))
		return ("newline");*/
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return ("|");
	if (is_special_operatoro(current->type))
		return ("newline");
	current = tokens;
	while (current)
	{
		if (is_special_operatoro(current->type))
		{
			if ((current->next) && (is_special_operatoro(current->next->type) || current->next->type == TOKEN_PIPE))

				return (current->next->content);
		}
		current = current->next;
	}
	return (NULL);
}

void	redirects_error(char *text, t_shell *shell)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, text, strlen(text));
    write(2, "'\n", 2);
	shell->exit_status = 2;
}

t_pipeline	*process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;
	int			hata;
	char		*error;

	hata = 0;
	if (!input || !*input)
		return (NULL);
	if (!syntax_check(input))
		hata = 1;
	tokens = advanced_lexer(input);
	if (!tokens)
		return (NULL);
	mark_eof_tokens(tokens);
	improved_expand_tokens(tokens, shell->environment);
	post_expansion_tokenize(&tokens);
	remove_quotes_from_tokens(tokens);
	if (check_redirects_strings(tokens))
	{
		error = check_redirects_strings(tokens);
		hata = 2;
	}

	pipeline = split_by_pipes(tokens);
	if (!pipeline)
	{
		hata = 3;
		free_token_array(tokens);
		return (NULL);
	}
	classify_pipeline_tokens(pipeline);


	if (hata == 1)
	{
		printf("❌ ❌ ❌Tırnak hatasssııı \n ");
		free_pipeline(pipeline);
		free_token_array(tokens);
		return NULL;
	}
	else if (hata == 2)
	{
		redirects_error(error, shell);
		free_pipeline(pipeline);
		free_token_array(tokens);
		return NULL;
	}
	free_token_array(tokens);
	return (pipeline);
}

void	process_command(t_shell *shell, char *command)
{
	if (!shell || !command)
		return ;

	cleanup_previous_state(shell);
	shell->pipeline = process_input(command, shell);
	if (!shell->pipeline)
		return ;
	if (!builds_commands_from_pipeline(shell))
		return ;
	if (!setup_file_descriptors(shell))
		return ;
	executer(shell);
	// print_shell_info(shell);
}
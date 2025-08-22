#include "../../../includes/minishell.h"

int	is_redirection_file(t_token *token)
{
	if (!token || !token->prev)
		return (FALSE);

	return (token->prev->type == TOKEN_REDIRECT_IN ||
			token->prev->type == TOKEN_REDIRECT_OUT ||
			token->prev->type == TOKEN_APPEND);
}

int	is_heredoc_delimeter(t_token *token)
{
	if (!token || !token->prev)
		return (FALSE);

	return (token->prev->type == TOKEN_HEREDOC &&
			(token->type == TOKEN_EOF || token->type == TOKEN_EOF_QUOTE));
}

char	*find_command_name(t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	while (curr)
	{
		if ((curr->type == TOKEN_COMMAND ||
			curr->type == TOKEN_WORD ||
			curr->type == TOKEN_FILE) &&
			!is_redirection_file(curr) &&
			!is_heredoc_delimeter(curr))
		{
			return (ft_strdup(ft_strtrim(curr->content, " \t")));
		}
		curr = curr->next;
	}
	return (NULL);
}

int	argument_counter(t_token *token_list)
{
	t_token	*curr;
	int		count;
	char	*cmd_name;

	cmd_name = find_command_name(token_list);
	if (!cmd_name)
		return (0);
	count = 1;
	curr = token_list;
	while (curr)
	{
		if ((curr->type == TOKEN_ARGUMENT && !is_heredoc_delimeter(curr)) ||
			((curr->type == TOKEN_WORD || curr->type == TOKEN_FILE) &&
			!is_redirection_file(curr) && !is_heredoc_delimeter(curr) &&
			ft_strcmp(curr->content, cmd_name) != 0))
		{
			count++;
		}
		curr = curr->next;
	}
	free(cmd_name);
	return (count);
}

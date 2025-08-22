#include "../../../includes/minishell.h"

static int	is_valid_argument_token(t_token *token, const char *cmd_name)
{
	if (!token || !cmd_name)
		return (FALSE);
	if (token->type == TOKEN_ARGUMENT && !is_heredoc_delimeter(token))
		return (TRUE);
	if ((token->type == TOKEN_WORD || token->type == TOKEN_FILE) &&
		!is_redirection_file(token) && !is_heredoc_delimeter(token) &&
		ft_strcmp(token->content, cmd_name) != 0)
		return (TRUE);
	return (FALSE);
}

static int	fill_command_arguments(t_command *cmd, t_token *token_list, int arg_count)
{
	t_token	*curr;
	int		i;
	char	*cmd_name;

	cmd_name = find_command_name(token_list);
	if (!cmd_name)
		return (FALSE);
	cmd->arguments = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->arguments)
		return (free(cmd_name), FALSE);
	cmd->cmd = ft_strdup(cmd_name);
	cmd->arguments[0] = ft_strdup(cmd_name);
	curr = token_list;
	i = 1;
	while (curr && i < arg_count)
	{
		if (is_valid_argument_token(curr, cmd_name))
			cmd->arguments[i++] = ft_strdup(curr->content);
		curr = curr->next;
	}
	cmd->arguments[i] = NULL;
	free(cmd_name);
	return (TRUE);
}

static int	extract_command_and_args(t_command *cmd, t_token *token_list)
{
	int	arg_count;

	arg_count = argument_counter(token_list);
	if (arg_count == 0)
		return (FALSE);
	return (fill_command_arguments(cmd, token_list, arg_count));
}

static void	extract_redirections_and_heredocs(t_command *cmd, t_token *token_list)
{
	t_token	*curr;
	int		is_quoted;

	curr = token_list;
	while (curr)
	{
		if (curr->type == TOKEN_REDIRECT_IN && curr->next &&
			curr->next->type == TOKEN_FILE)
			cmd->input_file = ft_strdup(curr->next->content);
		else if (curr->type == TOKEN_REDIRECT_OUT && curr->next &&
			curr->next->type == TOKEN_FILE)
			cmd->output_file = ft_strdup(curr->next->content);
		else if (curr->type == TOKEN_APPEND && curr->next &&
			curr->next->type == TOKEN_FILE)
			(cmd->output_file = ft_strdup(curr->next->content), cmd->append_mode = 1);
		else if (curr->type == TOKEN_HEREDOC && curr->next &&
			(curr->next->type == TOKEN_EOF || curr->next->type == TOKEN_EOF_QUOTE))
		{
			is_quoted = (curr->next->type == TOKEN_EOF_QUOTE);
			add_heredoc_delimiter_with_quote(cmd, curr->next->content, is_quoted);
		}
		curr = curr->next;
	}
}

t_command	*create_command_from_tokens(t_token *token_list)
{
	t_command	*cmd;
	t_token		*curr;

	if (!token_list)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->fd_out = STDOUT_FILENO;
	curr = token_list;
	while (curr && curr->prev)
		curr = curr->prev;
	if (!extract_command_and_args(cmd, curr))
	{
		free(cmd);
		return (NULL);
	}
	extract_redirections_and_heredocs(cmd, curr);
	return (cmd);
}

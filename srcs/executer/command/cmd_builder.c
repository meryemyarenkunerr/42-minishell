#include "../../../includes/minishell.h"

void	extract_redirections_and_heredocs(t_command *cmd, t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == TOKEN_REDIRECT_IN && curr->next && curr->next->type == TOKEN_FILE)
			cmd->input_file = ft_strdup(curr->next->content);
		else if (curr->type == TOKEN_REDIRECT_OUT && curr->next && curr->next->type == TOKEN_FILE)
			cmd->output_file = ft_strdup(curr->next->content);
		else if (curr->type == TOKEN_APPEND && curr->next && curr->next->type == TOKEN_FILE)
		{
			cmd->output_file = ft_strdup(curr->next->content);
			cmd->append_mode = 1;
		}
		else if (curr->type == TOKEN_HEREDOC && curr->next)
			add_heredoc_delimiter(cmd, curr->next->content);
		curr = curr->next;
	}
}

int	extract_command_and_args(t_command *cmd, t_token *token_list)
{
	int	arg_count;

	arg_count = argument_counter(token_list);
	if (arg_count == 0)
		return (FALSE);
	return (fill_command_arguments(cmd, token_list, arg_count));
}

int	builds_commands_from_pipeline(t_shell *shell)
{
	int			i;
	t_command	*curr;
	t_command	*prev;

	if (!shell || !shell->pipeline || !shell->pipeline->token_lists)
		return (FALSE);
	prev = NULL;
	i = 0;
	while (i < shell->pipeline->count)
	{
		curr = create_command_from_tokens(shell->pipeline->token_lists[i]);
		if (!curr)
			return (cleanup_and_return_error(shell));
		if (prev)
			prev->next = curr;
		else // head
			shell->commands = curr;
		prev = curr;
		i++;
	}
	return (TRUE);
}
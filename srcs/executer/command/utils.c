#include "../../../includes/minishell.h"

t_command	*create_empty_command_with_redirections(t_token *token_list)
{
	t_command	*cmd;
	t_token		*current;
	int			is_quoted;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->fd_out = STDOUT_FILENO;
	current = token_list;
	is_quoted = 0;
	while (current)
	{
	if (current->type == TOKEN_REDIRECT_IN && current->next)
	{
		cmd->input_file = ft_strdup(current->next->content);
		current = current->next;
	}
	else if (current->type == TOKEN_REDIRECT_OUT && current->next)
	{
		cmd->output_file = ft_strdup(current->next->content);
		current = current->next;
	}
	else if (current->type == TOKEN_APPEND && current->next)
	{
		cmd->output_file = ft_strdup(current->next->content);
		cmd->append_mode = 1;
		current = current->next;
	}
	else if (current->type == TOKEN_HEREDOC && current->next)
	{
		if (current->next->type == TOKEN_EOF_QUOTE)
			is_quoted = 1;
		add_heredoc_delimiter_with_quote(cmd, current->next->content, is_quoted);
		current = current->next;
	}
	current = current->next;
	}
	return (cmd);
}
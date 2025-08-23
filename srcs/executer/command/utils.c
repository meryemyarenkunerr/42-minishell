#include "../../../includes/minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->fd_out = STDOUT_FILENO;
	return (cmd);
}

t_token	*handle_redirection(t_command *cmd, t_token *current)
{
	int	is_quoted;

	if (current->type == TOKEN_REDIRECT_IN && current->next)
	{
		add_input_file(cmd, current->next->content);
		return (current->next);
	}
	else if (current->type == TOKEN_REDIRECT_OUT && current->next)
	{
		add_output_file(cmd, current->next->content, 0);
		return (current->next);
	}
	else if (current->type == TOKEN_APPEND && current->next)
	{
		add_output_file(cmd, current->next->content, 1);
		return (current->next);
	}
	else if (current->type == TOKEN_HEREDOC && current->next)
	{
		is_quoted = (current->next->type == TOKEN_EOF_QUOTE);
		add_heredoc_delimiter_with_quote(cmd, current->next->content,
			is_quoted);
		return (current->next);
	}
	return (current);
}

void	add_input_file(t_command *cmd, const char *filename)
{
	char	**new_files;
	int		i;

	if (!cmd || !filename)
		return ;
	new_files = malloc((cmd->input_count + 2) * sizeof(char *));
	if (!new_files)
		return ;
	i = 0;
	while (i < cmd->input_count)
	{
		new_files[i] = cmd->input_files[i];
		i++;
	}
	new_files[cmd->input_count] = ft_strdup(filename);
	new_files[cmd->input_count + 1] = NULL;
	if (cmd->input_files)
		free(cmd->input_files);
	cmd->input_files = new_files;
	cmd->input_count++;
}

t_command	*create_empty_command_with_redirections(t_token *token_list)
{
	t_command	*cmd;
	t_token		*current;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	current = token_list;
	while (current)
	{
		current = handle_redirection(cmd, current);
		current = current->next;
	}
	return (cmd);
}

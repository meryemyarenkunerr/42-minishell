#include "../../../includes/minishell.h"

void	add_heredoc_delimiter(t_command *cmd, const char *delimiter)
{
	char	**delimiter_list;
	int		i;

	if (!cmd || !delimiter)
		return ;
	delimiter_list = malloc((cmd->heredoc_count + 1 + 1) * sizeof(char *));
	if (!delimiter_list)
		return ;
	i = 0;
	while (i < cmd->heredoc_count) // eğer daha önce içeride varsa aktarma yapılıyor
	{
		delimiter_list[i] = ft_strdup(cmd->heredoc_delimiter[i]);
		i++;
	}
	delimiter_list[cmd->heredoc_count] = ft_strdup(delimiter);
	delimiter_list[cmd->heredoc_count + 1] = NULL;
	if (cmd->heredoc_delimiter)
		free_string_array(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = delimiter_list;
	cmd->heredoc_count++;
}

int	fill_command_arguments(t_command *cmd, t_token *token_list, int arg_count)
{
	t_token	*curr;
	int		i;

	cmd->arguments = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->arguments)
		return (FALSE);
	curr = token_list;
	i = 0;
	while (curr)
	{
		if (curr->type == TOKEN_COMMAND)
		{
			cmd->cmd = ft_strdup(curr->content);
			cmd->arguments[i++] = ft_strdup(curr->content);
		}
		else if (curr->type == TOKEN_ARGUMENT && !is_heredoc_delimeter(curr))
			cmd->arguments[i++] = ft_strdup(curr->content);
		curr = curr->next;
	}
	cmd->arguments[i] = NULL;
	return (TRUE);
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
	cmd->fd_in = STDIN_FILENO;
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
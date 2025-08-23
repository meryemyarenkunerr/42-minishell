#include "../../../includes/minishell.h"

void	add_heredoc_delimiter_with_quote(t_command *cmd, const char *delimiter,
	int is_quoted)
{
	char	**new_delimiters;
	int		i;

	if (!cmd || !delimiter)
		return ;
	new_delimiters = malloc((cmd->heredoc_count + 2) * sizeof(char *));
	if (!new_delimiters)
		return ;
	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (cmd->heredoc_delimiter && cmd->heredoc_delimiter[i])
			new_delimiters[i] = ft_strdup(cmd->heredoc_delimiter[i]);
		else
			new_delimiters[i] = ft_strdup("");
		i++;
	}
	new_delimiters[cmd->heredoc_count] = ft_strdup(delimiter);
	new_delimiters[cmd->heredoc_count + 1] = NULL;
	cmd->quote_flag = is_quoted;
	if (cmd->heredoc_delimiter)
		free_string_array(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = new_delimiters;
	cmd->heredoc_count++;
}

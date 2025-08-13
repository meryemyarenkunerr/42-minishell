#include "../../includes/minishell.h"

static void	cleanup_partial_heredoc_delimeters(char **delimeters, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(delimeters[i]);
		i++;
	}
}

static int	fill_heredoc_delimeter(t_shell *shell, t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->arguments[i])
	{
		if (is_heredoc_redirection(cmd->arguments[i]) && cmd->arguments[i + 1])
		{
			cmd->heredoc_delimeter[j] = ft_strdup(cmd->arguments[i + 1]);
			if (!cmd->heredoc_delimeter[j])
			{
				cleanup_partial_heredoc_delimeters(cmd->heredoc_delimeter, j);
				printf("error: malloc failed\n");
				shell->exit_status = 1;
				return FALSE;
			}
			j++;
		}
		i++;
	}
	cmd->heredoc_delimeter[j] = NULL;
	return TRUE;
}

static int	count_heredocs_in_command(t_command *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->arguments && cmd->arguments[i])
	{
		if (is_heredoc_redirection(cmd->arguments[i]))
			count++;
		i++;
	}
	return (count);
}

// heredoc_delimeter ve heredoc_count doldurma
int	fill_heredoc_delimeter_and_count(t_shell *shell, t_command *cmd)
{
	if (!cmd || !cmd->arguments)
		return FALSE;
	cmd->heredoc_count = count_heredocs_in_command(cmd);
	if (cmd->heredoc_delimeter)
		free_heredoc_delimiters(cmd->heredoc_delimeter);
	cmd->heredoc_delimeter = malloc(sizeof(char *) * (cmd->heredoc_count + 1)); // +1 -> NULL
	if (!cmd->heredoc_delimeter)
		return FALSE;
	if (!fill_heredoc_delimeter(shell, cmd))
	{
		printf("error: malloc failed\n");
		shell->exit_status = 1;
		return FALSE;
	}
	return TRUE;
}
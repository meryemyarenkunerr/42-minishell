#include "../../includes/minishell.h"

static int	arg_count(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return count;
}

static char	**filter_redirections(t_command *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = malloc(sizeof(char *) * (arg_count(cmd->arguments) + 1));
	if (!new_args)
		return NULL;
	i = 0;
	j = 0;
	while (cmd->arguments[i])
	{
		if (is_input_redirection(cmd->arguments[i]) ||
			is_output_redirection(cmd->arguments[i]) ||
			is_appended_redirection(cmd->arguments[i]) ||
			is_heredoc_redirection(cmd->arguments[i]))
		{
			i += 2;
			continue ;
		}
		new_args[j++] = ft_strdup(cmd->arguments[i++]);
	}
	new_args[j] = NULL;
	return new_args;
}

static void	remove_redirections_from_args(t_shell *shell, t_command *cmd)
{
	char	**new_args;

	if (!cmd || !cmd->arguments)
		return ;
	new_args = filter_redirections(cmd);
	if (!new_args)
	{
		printf("error: malloc failed\n");
		shell->exit_status = 1;
		return ;
	}
	free_array(cmd->arguments);
	cmd->arguments = new_args;
}

// yönlendirmeleri (input/output) dolduran fonksiyon
static int	fill_redirections(t_shell *shell, t_command *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = TRUE;
	while (cmd->arguments && cmd->arguments[i])
	{
		if (is_input_redirection(cmd->arguments[i]))
			set_input_file(shell, cmd, cmd->arguments[++i], &flag);
		else if (is_output_redirection(cmd->arguments[i]))
			set_output_file(shell, cmd, cmd->arguments[++i], FALSE, &flag);
		else if (is_appended_redirection(cmd->arguments[i]))
			set_output_file(shell, cmd, cmd->arguments[++i], TRUE, &flag);
		else if (is_heredoc_redirection(cmd->arguments[i]))
		{
			i++;
			if (!fill_heredoc_delimeter_and_count(shell, cmd))
				return FALSE;
			flag = TRUE;
		}
		if (!flag)
			return FALSE;
		i++;
	}
	return TRUE;
}

// ana fonksiyon
int	filler_commands(t_shell *shell)
{
	t_command	*current;

	current = shell->commands;
	while (current)
	{
		if (!fill_redirections(shell, current))
			return FALSE;
		remove_redirections_from_args(shell, current);
		current = current->next;
	}
	return TRUE;
}
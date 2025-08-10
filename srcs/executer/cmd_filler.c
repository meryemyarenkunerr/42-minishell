#include "../../includes/minishell.h"

// yönlendirmeleri (input/output) dolduran fonksiyon
int	fill_redirections(t_shell *shell, t_command *cmd)
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
		current = current->next;
	}
	return TRUE;
}
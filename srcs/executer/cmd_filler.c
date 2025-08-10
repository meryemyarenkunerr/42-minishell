#include "../../includes/minishell.h"

// yönlendirmeleri (input/output) dolduran fonksiyon
void	fill_redirections(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->arguments && cmd->arguments[i])
	{
		if (is_input_redirection(cmd->arguments[i]))
			set_input_file(cmd, cmd->arguments[++i]);
		else if (is_output_redirection(cmd->arguments[i]))
			set_output_file(cmd, cmd->arguments[++i], FALSE);
		else if (is_appended_redirection(cmd->arguments[i]))
			set_output_file(cmd, cmd->arguments[++i], TRUE);
		i++;
	}
}

// ana fonksiyon
void	filler_commands(t_command *commands)
{
	t_command	*current;

	current = commands;
	while (current)
	{
		fill_redirections(current);
		current = current->next;
	}
}
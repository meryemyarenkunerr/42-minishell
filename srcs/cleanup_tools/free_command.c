#include "../../includes/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_single_command(t_command *command)
{
	if (!command)
		return ;
	if (command->cmd)
		free(command->cmd);
	if (command->arguments)
		free_string_array(command->arguments);
	if (command->heredoc_delimiter)
		free_string_array(command->heredoc_delimiter);
	if (command->input_file)
		free(command->input_file);
	if (command->output_file)
		free(command->output_file);
	if (command->fd_in > STDERR_FILENO)
		close(command->fd_in);
	if (command->fd_out > STDERR_FILENO)
		close(command->fd_out);
	free(command);
}

void	free_command_list(t_command *commands)
{
	t_command	*curr;
	t_command	*next;

	curr = commands;
	while (curr)
	{
		next = curr->next;
		free_single_command(curr);
		curr = next;
	}
}

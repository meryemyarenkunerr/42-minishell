#include "../../includes/minishell.h"

static t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->arguments = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;
	return (cmd);
}

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**parse_arguments(t_token **tokens)
{
	char	**args;
	int		arg_count;
	int		i;

	arg_count = count_args(*tokens);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE && i < arg_count)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			args[i] = ft_strdup((*tokens)->content);
			if (!args[i])
			{
				free_array(args);
				return (NULL);
			}
			i++;
		}
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

t_command	*parser(t_token *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	if (!tokens)
		return (NULL);
	head = NULL;
	while (tokens)
	{
		new_cmd = create_command();
		if (!new_cmd)
		{
			free_commands(head);
			return (NULL);
		}
		new_cmd->arguments = parse_arguments(&tokens);
		if (!head)
			head = new_cmd;
		else
		{
			current = head;
			while (current->next)
				current = current->next;
			current->next = new_cmd;
		}
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head);
}

void	free_commands(t_command *cmd_list)
{
	t_command	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		if (temp->arguments)
			free_array(temp->arguments);
		if (temp->input_file)
			free(temp->input_file);
		if (temp->output_file)
			free(temp->output_file);
		free(temp);
	}
}

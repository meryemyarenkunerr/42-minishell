/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:32:58 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_command	*parser_loop(t_token *tokens, t_command *head,
	t_command *current, t_command	*new_cmd)
{
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

t_command	*parser(t_token *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	if (!tokens)
		return (NULL);
	head = NULL;
	current = NULL;
	new_cmd = NULL;
	return (parser_loop(tokens, head, current, new_cmd));
}

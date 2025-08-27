/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 05:06:30 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	extract_redirections_and_heredocs(t_command *cmd,
	t_token *token_list)
{
	t_token	*curr;
	int		is_quoted;

	curr = token_list;
	is_quoted = 0;
	while (curr)
	{
		if (curr->type == TOKEN_REDIRECT_IN)
			add_input_file(cmd, curr->next->content);
		else if (curr->type == TOKEN_REDIRECT_OUT)
			add_output_file(cmd, curr->next->content, 0);
		else if (curr->type == TOKEN_APPEND)
			add_output_file(cmd, curr->next->content, 1);
		else if (curr->type == TOKEN_HEREDOC)
		{
			if (curr->next->type == TOKEN_EOF_QUOTE)
				is_quoted = 1;
			add_heredoc_delimiter_with_quote(cmd, curr->next->content,
				is_quoted);
		}
		curr = curr->next;
	}
}

static int	argument_counter(t_token *token_list)
{
	t_token	*curr;
	int		count;
	char	*cmd_name;

	cmd_name = find_command_name(token_list);
	if (!cmd_name)
		return (0);
	count = 1;
	curr = token_list;
	while (curr)
	{
		if (curr->type == TOKEN_ARGUMENT
			|| curr->type == TOKEN_COMMAND)
			count++;
		curr = curr->next;
	}
	free(cmd_name);
	return (count);
}

static int	extract_command_and_args(t_command *cmd, t_token *token_list)
{
	int	arg_count;

	arg_count = argument_counter(token_list);
	if (arg_count == 0)
		return (FALSE);
	return (fill_command_arguments(cmd, token_list, arg_count));
}

t_command	*create_empty_command_with_redirections(t_token *token_list)
{
	t_command	*cmd;
	t_token		*current;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	current = token_list;
	extract_redirections_and_heredocs(cmd, current);
	return (cmd);
}

t_command	*create_command_from_tokens(t_token *token_list)
{
	t_command	*cmd;
	t_token		*curr;

	if (!token_list)
		return (NULL);
	cmd = init_command();
	if (!cmd)
		return (NULL);
	curr = token_list;
	if (!extract_command_and_args(cmd, curr))
	{
		free(cmd);
		return (NULL);
	}
	extract_redirections_and_heredocs(cmd, curr);
	return (cmd);
}

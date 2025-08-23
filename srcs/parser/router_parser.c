/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:28:27 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 20:25:50 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_syntax_or_error(char *input)
{
	if (!syntax_check(input))
	{
		quote_error();
		return (0);
	}
	return (1);
}

static int	check_redirects_or_error(t_token *tokens,
				t_pipeline *pipeline, t_shell *shell)
{
	char	*error;

	error = check_redirects_strings(tokens);
	if (error)
	{
		redirects_error(error, shell);
		if (pipeline)
			free_pipeline(pipeline);
		free_token_array(tokens);
		return (0);
	}
	return (1);
}

static t_pipeline	*build_pipeline(t_token *tokens)
{
	t_pipeline	*pipeline;

	pipeline = split_by_pipes(tokens);
	if (!pipeline)
	{
		free_token_array(tokens);
		return (NULL);
	}
	classify_pipeline_tokens(pipeline);
	return (pipeline);
}

static t_token	*prepare_tokens(char *input, t_shell *shell)
{
	t_token	*tokens;

	tokens = advanced_lexer(input);
	if (!tokens)
		return (NULL);
	mark_eof_tokens(tokens);
	improved_expand_tokens(tokens, shell);
	post_expansion_tokenize(&tokens);
	remove_quotes_from_tokens(tokens);
	return (tokens);
}

t_pipeline	*process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (!input || !*input)
		return (NULL);
	if (!check_syntax_or_error(input))
		return (NULL);
	tokens = prepare_tokens(input, shell);
	if (!tokens)
		return (NULL);
	pipeline = build_pipeline(tokens);
	if (!pipeline)
		return (NULL);
	if (!check_redirects_or_error(tokens, pipeline, shell))
		return (NULL);
	free_token_array(tokens);
	return (pipeline);
}

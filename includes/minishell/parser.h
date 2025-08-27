/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 08:08:03 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../structs.h"

t_token			*advanced_lexer(char *input);
int				is_whitespace(char c);
int				is_quote(char c);
int				is_redirect_operator(char c);
int				is_pipe(char c);
int				skip_whitespace(char *input, int *i);
t_token_types	get_advanced_token_type(char *str);
char			*extract_operator(char *input, int *i);
char			*extract_word_until_delimiter(char *input, int *i);
char			*extract_quoted_string(char *input, int *i);
void			add_token_to_list(t_token **head, t_token *new_token);
t_token			*create_token(char *content, t_token_types type);
char			*check_redirects_strings(t_token *tokens);
void			mark_eof_tokens(t_token *tokens);
void			improved_expand_tokens(t_token *tokens, t_shell *shell);
int				is_valid_var_char(char c);
char			*extract_var_name(char *str, int start, int *end);
char			*get_var_value(char *var_name, t_env *env);
char			*append_exit_status(char *result, t_shell *shell, int *i);
t_pipeline		*split_by_pipes(t_token *tokens);
void			fill_pipeline_segments(t_pipeline *pipeline, t_token *tokens);
void			post_expansion_tokenize(t_token **head);
char			**split_by_whitespace_respect_quotes(char *str);
void			remove_quotes_from_tokens(t_token *tokens);
int				syntax_check(char *input);
void			classify_pipeline_tokens(t_pipeline *pipeline);
t_pipeline		*process_input(char *input, t_shell *shell);

#endif

#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H

#include "../structs.h"

/* ADVANCED LEXER */
/* advanced_lexer.c */
t_token			*advanced_lexer(char *input);
/* advanced_lexer_utils.c */
int				is_whitespace(char c);
int				is_quote(char c);
int				is_redirect_operator(char c);
int				is_pipe(char c);
int				skip_whitespace(char *input, int *i);
/* advanced lexer utils two*/
t_token_types	get_advanced_token_type(char *str);
char			*extract_operator(char *input, int *i);
char			*extract_word_until_delimiter(char *input, int *i);
char			*extract_quoted_string(char *input, int *i);

/* advanced lexer utils three */
void			add_token_to_list(t_token **head, t_token *new_token);
t_token			*create_token(char *content, t_token_types type);

/* REDIRECTS CHECK */
/* redirects Check */
char			*check_redirects_strings(t_token *tokens);

/* EOF CHECK*/
/* eof_check */
void			mark_eof_tokens(t_token *tokens);

/* IMPROVED EXPANDER */
/* improved_expander.c */
void			improved_expand_tokens(t_token *tokens, t_shell *shell);
/* improved_expander_utils.c */
int				is_valid_var_char(char c);
char			*extract_var_name(char *str, int start, int *end);
char			*get_var_value(char *var_name, t_env *env);
char			*append_exit_status(char *result, t_shell *shell, int *i);

/* PIPELINE TOKENIZER */
/* pipeline_tokenizer.c */
t_pipeline		*split_by_pipes(t_token *tokens);
/* pipeline_tokenizer_utils.c*/
void			fill_pipeline_segments(t_pipeline *pipeline, t_token *tokens);

/* POST EXPANDER */
/* post_expander.c */
void			post_expansion_tokenize(t_token **head);
/* post_expander_utils.c*/
char			**split_by_whitespace_respect_quotes(char *str);

/* QUOTE REMOVER */
/* quote_remover.c */
void			remove_quotes_from_tokens(t_token *tokens);

/* SYNTAX CHECK */
/* Syntax Check */
int				syntax_check(char *input);

/* TOKEN CLASSIFIER */
/* token_classifier.c */
void			classify_pipeline_tokens(t_pipeline *pipeline);

/* PARSER */
/* router_parser.c */
t_pipeline		*process_input(char *input, t_shell *shell);

#endif // MINISHELL_PARSER_H

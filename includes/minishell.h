#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard Libraries */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Own Headers */
# include <../libft/libft.h>
# include "defines.h"
# include "structs.h"

/* Global Variable */
int		g_sigint_received;

/* Functions */
/* init_shell.c */
void		init_shell(t_shell *shell, char **env);

/* env_utils.c */
t_env		*init_env(char **env);
void		free_env_list(t_env *env);

/* free.c */
void		free_env_list(t_env *env);
void		free_at_exit(t_shell *shell);

/* shell_loop.c */
void		shell_loop(t_shell *shell);

/* signals.c */
void		setup_signal_handler(struct termios *term_backup);

/* prompt_utils.c */
void		build_prompt(t_shell *shell);

/* advanced_lexer.c */
t_token		*advanced_lexer(char *input);

/* improved_expander.c */
void		improved_expand_tokens(t_token *tokens, t_env *env);

/* quote_remover.c */
void		remove_quotes_from_tokens(t_token *tokens);

/* post_expander.c */
void		post_expansion_tokenize(t_token **head);

/* parser.c */
t_command	*parser(t_token *tokens);
void		free_commands(t_command *cmd_list);

/* lexer.c */
t_token		*lexer(char *input);
void		free_tokens(t_token *tokens);
t_token		*create_token(char *content, t_token_types type);
void		add_token_to_list(t_token **head, t_token *new_token);

/* utils.c */
t_env		*copy_env(char **envp);
void		free_array(char **array);
char		*get_env_value(t_env *env, char *key);
void		set_env_value(t_env **env, char *key, char *value);

/* pipeline_tokenizer.c */
t_pipeline	*split_by_pipes(t_token *tokens);
void		free_pipeline(t_pipeline *pipeline);

/* token_classifier.c */
void		classify_pipeline_tokens(t_pipeline *pipeline);

/* executer.c */
void	executer(t_shell *shell, t_pipeline *pipeline, t_token *tokens);

/* redirections.c */
int	check_redirection_syntax(t_shell *shell, t_token *tokens);

/* heredoc.c */
int	has_heredoc(t_token *tokens);











/* temp_creator.c */
t_token	*create_token_temp(char *content, t_token_types type);
void append_token(t_token **head, t_token *new_token);
t_token *build_token_list();
t_pipeline *split_pipeline(t_token *tokens);
t_command *build_commands(t_pipeline *pipeline);
void print_commands(t_command *cmds);
void print_tokens(t_token *head);
void print_pipeline(t_pipeline *pipeline);
void free_token_list_temp(t_token *head);
void free_pipeline_temp(t_pipeline *pipeline);
void free_commands_temp(t_command *cmd);
void free_token_list(t_token *token);

#endif
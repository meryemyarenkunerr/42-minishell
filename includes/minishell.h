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
/* main */
void	init_shell(t_shell *shell, char **env);
void	shell_loop(t_shell *shell);
void	build_prompt(t_shell *shell);
char	*read_line(t_shell *shell);
int		is_exit_command_received(t_shell *shell, char *command);
void	sigint_received(t_shell *shell);
int		process_command(t_shell *shell, char *command);

/* signal */
int		handle_signal_and_exit(t_shell *shell, char **command);
void	setup_signal_handler(struct termios *term_backup);


/* free.c */
void		free_env_list(t_env *env);
void		free_at_exit(t_shell *shell);

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
char **create_arguments_temp_fixed(int count, const char **args);
char **create_heredoc_delimiters_temp_fixed(int count, const char **delims);
t_command *create_command_temp(const char *cmd, char **arguments,
                              char *input_file, char *output_file,
                              int append_mode, char **heredoc_delim);
t_command *build_commands_for_example_temp(void);
void free_arguments_temp(char **args);
void free_heredoc_delimiters_temp(char **heredocs);
void free_command_temp(t_command *cmd);

#endif
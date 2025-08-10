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
void		init_shell(t_shell *shell, char **env);
void		shell_loop(t_shell *shell);
void		build_prompt(t_shell *shell);
char		*read_line(t_shell *shell);
int			is_exit_command_received(t_shell *shell, char *command);
void		sigint_received(t_shell *shell);
int			process_command(t_shell *shell, char *command);

/* signal */
int			handle_signal_and_exit(t_shell *shell, char **command);
void		setup_signal_handler(struct termios *term_backup);

/* executer */
void		executer(t_shell *shell);
void		filler_commands(t_command *commands);
void		set_output_file(t_command *cmd, char *file, int append);
void		set_input_file(t_command *cmd, char *file);
int			is_input_redirection(const char *arg);
int			is_output_redirection(const char *arg);
int			is_appended_redirection(const char *arg);




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










/* temp files */
t_command *create_command_cat_heredoc_temp(void);
t_command *create_command_wc_l_temp(void);
t_pipeline *create_pipeline_cat_wc_temp(void);
void free_arguments_temp(char **args);
void free_heredoc_delimiters_temp(char **heredocs);
void free_command_temp(t_command *cmd);
void free_pipeline_token_lists_temp(t_pipeline *pipeline);
void free_pipeline_temp(t_pipeline *pipeline);
void print_shell_info(t_shell *shell);
char **create_args_temp(int count, char **args);

// farklı komut kombinasyonları
void fill_shell_commands_and_pipeline_temp(t_shell *shell);
void fill_shell_cat_input_temp(t_shell *shell);
void fill_shell_echo_output_temp(t_shell *shell);
void fill_shell_echo_append_temp(t_shell *shell);

#endif
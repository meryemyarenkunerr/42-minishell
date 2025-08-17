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
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Own Headers */
# include <../libft/libft.h>
# include "defines.h"
# include "structs.h"

/* Global Variable */
extern int	g_sigint_received;

/* Functions */

/* signal */
/* signals.c */
int			handle_signal_and_exit(t_shell *shell, char **command);
void		check_and_warn(int ret, const char *msg);
void		handle_sigint(int signo);
void		sigint_received(t_shell *shell);

/* signals_2.c */
void		heredoc_signal_handler(int signo);

/* main */
/* init_env.c */
int			add_key_value_pair(t_env **env, char *env_pair);
int			extract_key_value(char *env_pair, char **key, char **val);
t_env		*create_env_node(char *key, char *val);
t_env		*create_env_node_empty();
void		add_new_env_node(t_env **env, t_env *tail);

/* init.c */
void		init_shell(t_shell *shell, char **env);
t_env		*init_env(char **env);
void		init_signal();
void		init_simple_signal(int signo);

/* process_command.c */
void		process_command(t_shell *shell, char *command);

/* prompt.c */
char		*build_prompt();

/* shell_loop.c */
void		shell_loop(t_shell *shell);
int			is_exit(t_shell *shell);

/* error */
/* errors.c */
int			handle_fork_error(int fds[2]);
void		handle_export_error(t_shell *shell, const char *arg);

/* cleanup_tools */
/* free.c */
void		cleanup_previous_state(t_shell *shell);
void		free_at_exit(t_shell *shell);

/* free_env.c */
void		free_env_list(t_env *env);
void		free_env_node(t_env *node);

/* free_pipeline.c */
void	free_pipeline(t_pipeline *pipeline);
void	free_token_array(t_token *tokens);

/* free_command.c */
void		free_command_list(t_command *commands);
void		free_single_command(t_command *command);
void		free_string_array(char **array);

/* close_fds.c */
void		close_command_fds(t_command *cmd);
void		close_all_command_fds(t_shell *shell);

/* executer */
/* builtins_basics.c */
void		execute_builtin_pwd(t_shell *shell, t_command *cmd);
void		execute_builtin_echo(t_shell *shell, t_command *cmd);
void		execute_builtin_env(t_shell *shell, t_command *cmd);

/* builtins_cd.c */
void		execute_builtin_cd(t_shell *shell, t_command *cmd);
char		*get_cd_path(t_shell *shell, t_command *cmd);
int			update_current_dir(t_shell *shell);

/* builtins_export.c */
void		execute_builtin_export(t_shell *shell, t_command *cmd);
int			validate_export_arg(const char *arg);
void		process_export_arg(t_shell *shell, const char *arg);
void		mark_variable_exported(t_shell *shell, const char *key);
void		print_export_format(t_shell *shell);

/* builtins_export_util.c */
void		set_env_variable(t_shell *shell, const char *var_value);
t_env		*find_env_variable(t_env *env_list, const char *key);
void		add_env_variable(t_shell *shell, const char *key, const char *value);
void		append_env_node(t_shell *shell, t_env *new_env);

/* builtins_unset.c */
void		execute_builtin_unset(t_shell *shell, t_command *cmd);
void		remove_env_variable(t_shell *shell, const char *key);

/* cmd_filler.c */
int			builds_commands_from_pipeline(t_shell *shell);
t_command	*create_command_from_tokens(t_token *token_list);

/* executer.c */
void		executer(t_shell *shell);

/* cmd_builder.c */
int			builds_commands_from_pipeline(t_shell *shell);
int			extract_command_and_args(t_command *cmd, t_token *token_list);
void		extract_redirections_and_heredocs(t_command *cmd, t_token *token_list);

/* cmd_filler.c */
t_command	*create_command_from_tokens(t_token *token_list);
int			fill_command_arguments(t_command *cmd, t_token *token_list, int arg_count);
void		add_heredoc_delimiter(t_command *cmd, const char *delimiter);

/* cmd_utils.c */
int			argument_counter(t_token *token_list);
int			cleanup_and_return_error(t_shell *shell);

/* utils.c */
int			ft_strcmp(const char *s1, const char *s2);
int			is_builtin_command(const char *cmd);
void		execute_builtin(t_shell *shell, t_command *cmd);

/* redirections.c */
int			setup_file_descriptors(t_shell *shell);
int			setup_command_fds(t_command *cmd);
int			setup_output_redirection(t_command *cmd);
int			setup_input_redirection(t_command *cmd);

/* heredoc_handler.c */
int			setup_heredoc_fds(t_command *cmd);

/* heredoc_parent.c */
void		execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid);

/* heredoc_child.c */
void		execute_heredoc_child(t_command *cmd, int fds[2]);
void		handle_heredoc_input(t_command *cmd, int write_fd);
void		process_single_heredoc(char *delimiter, int write_fd);

/* single_command.c */
void		execute_single_command(t_shell *shell, t_command *cmd);











/* mock data creators and printer */
t_token	*create_token(const char *content, t_token_types type);
void	link_tokens(t_token *tokens[], int count);
void print_shell_info(t_shell *shell);
const char *get_token_type_name(t_token_types type);
void print_commands_only(t_shell *shell);

// farklı komut kombinasyonları
t_pipeline	*mock_cd();
t_pipeline	*mock_cd_dotdot();
t_pipeline	*mock_cd_temp();
t_pipeline	*mock_echo_n_hello();
t_pipeline	*mock_echo_hello_world();
t_pipeline	*mock_env();
t_pipeline	*mock_export_empty();
t_pipeline	*mock_export_invalid();
t_pipeline	*mock_export_path();
t_pipeline	*mock_export_multiple();
t_pipeline	*mock_export_myvar();
t_pipeline	*mock_export_list();
t_pipeline	*mock_pwd();
t_pipeline	*mock_unset_user();
t_pipeline	*mock_cat_heredoc();
t_pipeline	*mock_echo_append_heredoc();
t_pipeline	*mock_cat_heredoc_redirect();
t_pipeline	*mock_cat_double_heredoc();
t_pipeline	*mock_echo_append();
t_pipeline	*mock_cat_input();
t_pipeline	*mock_echo_redirect();

#endif
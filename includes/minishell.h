/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:01:40 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 21:18:36 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <readline/readline.h>
# include <readline/history.h>

/* Own Headers */
# include "../libft/libft.h"
# include "defines.h"
# include "structs.h"
# include "./minishell/error.h"
# include "./minishell/cleanup.h"
# include "./minishell/executer.h"
# include "./minishell/e_builtins.h"
# include "./minishell/e_command.h"
# include "./minishell/e_external.h"
# include "./minishell/e_heredoc.h"
# include "./minishell/e_multiple.h"
# include "./minishell/main.h"
# include "./minishell/parser.h"


/* Global Variable */
extern int	g_sigint_received;

/* Functions */

char			*safe_readline(const char *prompt, t_shell *shell, char *content, int fds[2]);

/* SIGNAL */
/* signals.c */
// int			handle_signal_and_exit(t_shell *shell, char **command);
// void			check_and_warn(int ret, const char *msg);
// void			handle_sigint(int signo);
// void			sigint_received(t_shell *shell);

void			handle_signals(void);
void			ctrl_c(int sig);
void			ctrl_d(int sig);
void			tcseta(void);

/* heredoc_signal.c */
void			heredoc_signal_handler(int signo);
void			setup_heredoc_signals(void);
void			restore_heredoc_signals(void);

/* MAIN */
/* init_env.c */
int				add_key_value_pair(t_env **env, char *env_pair);
int				extract_key_value(char *env_pair, char **key, char **val);
t_env			*create_env_node(char *key, char *val);
t_env			*create_env_node_empty(void);
void			add_new_env_node(t_env **env, t_env *tail);

/* init.c */
void			init_shell(t_shell *shell, char **env);
t_env			*init_env(char **env);
void			init_signal(void);
void			init_simple_signal(int signo);

/* process_command.c */
void			process_command(t_shell *shell, char *command);

/* prompt.c */
char			*build_prompt(void);

/* shell_loop.c */
void			shell_loop(t_shell *shell);
int				is_exit(t_shell *shell);

/* ERROR */
/* errors.c */
int				handle_fork_error(int fds[2]);
void			handle_export_error(t_shell *shell, char *arg);
void			command_not_found_error(t_shell *shell, char *cmd);
void			handle_execve_error(char *cmd);
pid_t			*handle_fork_error_multiple(pid_t *pids, int i);

/* builtins_error.c */
void			ft_exit(t_shell *shell, t_command *cmd);
void			numeric_argument_error_exit(t_shell *shell, t_command *cmd);
void			too_many_argument_error_exit(t_shell *shell, t_command *cmd);

/* syntax_error.c */
void			redirects_error(char *text, t_shell *shell);
void			quote_error(void);

/* heredoc_error.c */
void			print_eof_warning(char *delimiter);

/* CLEANUP_TOOLS */
/* free.c */
void			cleanup_previous_state(t_shell *shell);
void			free_at_exit(t_shell *shell);

/* free_pipes.c */
void			update_exit_status(int idx, int *exit_stat, int cmd_count,
					int status);
void			cleanup_pipeline(t_shell *shell, int **pipes, pid_t *pids,
					int cmd_count);
void			cleanup_pipes(int **pipes, int cmd_count);
void			cleanup_partial_pipes(int **pipes, int created_count);
void			cleanup_partial_processes(pid_t *pids, int created_count);

/* free_env.c */
void			free_env_list(t_env *env);
void			free_env_node(t_env *node);

/* free_pipeline.c */
void			free_pipeline(t_pipeline *pipeline);
void			free_token_array(t_token *tokens);

/* free_command.c */
void			free_command_list(t_command *commands);
void			free_single_command(t_command *command);
void			free_string_array(char **array);
int				cleanup_and_return_error(t_shell *shell);

/* close_fds.c */
void			close_command_fds(t_command *cmd);
void			close_all_command_fds(t_shell *shell);

/* close_pipes.c */
void			close_all_pipes_in_child(int **pipes, int cmd_count);
void			close_all_pipes_in_parent(int **pipes, int cmd_count);

/* free_builtins.c */
void			cleanup_cd_memory(char *old_pwd, char *target_dir);

/* free_heredoc.c */
void			complete_cleanup_and_exit(t_shell *shell, int exit_code);

/* EXECUTER */
/* executer.c */
void			executer(t_shell *shell);

/* utils.c */
int				ft_strcmp(const char *s1, const char *s2);
int	open_output_file(t_shell *shell, t_command *cmd, int i);
void	close_old_fd(int *fd_out);

/* redirections.c */
int				setup_file_descriptors(t_shell *shell);
int				setup_command_fds(t_shell *shell, t_command *cmd);
int				setup_output_redirection(t_shell *shell, t_command *cmd);
int				setup_input_redirection(t_shell *shell, t_command *cmd);

/* single_command.c */
void			execute_single_command(t_shell *shell, t_command *cmd);

/* multiple_command.c */
void			execute_pipeline_commands(t_shell *shell, int cmd_count);

/*	EXECUTER/BUILTINS */
/* builtins_basics.c */
void			execute_builtin_pwd(t_shell *shell, t_command *cmd);
void			execute_builtin_env(t_shell *shell, t_command *cmd);

/* builtins_echo.c */
void			execute_builtin_echo(t_shell *shell, t_command *cmd);
int				is_valid_echo_flag(const char *arg);
int				is_dollar_question_mark(t_shell *shell, const char *arg);

/* builtins_exit.c */
void			execute_builtin_exit(t_shell *shell, t_command *cmd);
int				is_valid_number(const char *str);

/* builtins_cd.c */
void			execute_builtin_cd(t_shell *shell, t_command *cmd);
char			*get_target_directory(t_shell *shell, const char *target_path);
char			*get_home_directory(t_shell *shell);
char			*expand_home_path(t_shell *shell, const char *target_path);
int				change_directory_safely(t_shell *shell, char *target_dir,
					char *old_pwd);

/* builtins_export.c */
void			execute_builtin_export(t_shell *shell, t_command *cmd);
void			print_export_variables(t_env *env);
int				process_export_arguments(t_shell *shell, const char *arg);
int				process_assignment(t_shell *shell, const char *arg,
					char *equal_pos);
int				process_mark_for_export(t_shell *shell, const char *key);

/* builtins_export_utils.c */
int				is_valid_identifier_export(const char *str);
int				count_env_keys(t_env *env);
void			copy_env_to_array(t_env *env, t_env **array);
void			sort_env_array(t_env **array, int size);

/* builtins_unset.c */
void			execute_builtin_unset(t_shell *shell, t_command *cmd);

/* builtin_utils.c */
int				is_builtin_command(const char *cmd);
void			execute_builtin(t_shell *shell, t_command *cmd);
void			restore_builtin_redirections(int saved_fds[2]);
void			call_builtin_function(t_shell *shell, t_command *cmd);
void			setup_builtin_redirections(t_command *cmd, int saved_fds[2]);

/* builtins_utils2.c */
char			*get_env_value(t_env *env, const char *key);
void			set_env_variable(t_env **env, const char *key, const char *val);
void			update_pwd_env(t_shell *shell, char *old_pwd);
void			remove_env_variable(t_env **env, const char *key);
int				cmd_counter_except_first(t_command *cmd);

/* EXECUTER/COMMAND */
/* command_builder.c */
int				builds_commands_from_pipeline(t_shell *shell);

/* heredoc_management.c */
void			add_heredoc_delimiter_with_quote(t_command *cmd,
					const char *delimiter, int is_quoted);

/* token_analysis.c */
int				is_redirection_file(t_token *token);
int				is_heredoc_delimeter(t_token *token);
char			*find_command_name(t_token *token_list);
int				argument_counter(t_token *token_list);

/* command_creation.c */
int				is_valid_argument_token(t_token *token, const char *cmd_name);
int				fill_command_arguments(t_command *cmd, t_token *token_list,
					int arg_count);
int				extract_command_and_args(t_command *cmd, t_token *token_list);
void			extract_redirections_and_heredocs(t_command *cmd,
					t_token *token_list);
t_command		*create_command_from_tokens(t_token *token_list);


/* utils.c */
t_command		*create_empty_command_with_redirections(t_token *token_list);
void			add_input_file(t_command *cmd, const char *filename);
t_token			*handle_redirection(t_command *cmd, t_token *current);
t_command		*init_command(void);

/* utils2.c */
void			add_output_file(t_command *cmd, const char *filename,
					int append_mode);

/* expander.c */
char			*expand_variable(char *line, t_shell *shell);

/* EXECUTER/HEREDOC */
/* heredoc_handler.c */
int				setup_heredoc_fds(t_shell *shell, t_command *cmd);

/* heredoc_parent.c */
void			execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid);

/* heredoc_child.c */
void			execute_heredoc_child(t_shell *shell, t_command *cmd,
					int fds[2]);
void	handle_heredoc_input(t_shell *shell, t_command *cmd, int fds[2]);
void			process_single_heredoc(t_shell *shell, char *delimiter,
					int fds[2]);
void			process_single_heredoc_ignore(t_shell *shell, char *delimiter,
					int fds[2]);

/* heredoc_utils.c */
int				is_heredoc_interrupted(void);
int				check_line_conditions(char *line, char *delimiter);
char			*process_line_content(t_shell *shell, char *line);
void			write_processed_line(int write_fd, char *processed_line);

/* EXECUTER/EXTERNAL */
/* external.c */
void			execute_external(t_shell *shell, t_command *cmd);
pid_t			fork_and_execute(t_shell *shell, t_command *cmd,
					char *exec_path);
void			wait_for_child(t_shell *shell, pid_t pid);

/* path.c */
char			*find_executable_path(t_shell *shell, char *cmd);
char			*check_direct_path(char *cmd);
char			*search_in_path(t_shell *shell, char *cmd);
char			*check_path_directories(char **path_dirs, char *cmd);
char			*build_full_path(char *dir, char *cmd);

/* external_child.c */
void			execute_child_process(t_shell *shell, t_command *cmd,
					char *exec_path);
char			**convert_env_to_array(t_env *env);
int				count_env_entries(t_env *env);
char			*create_env_string(char *key, char *val);

/* child_utils.c */
int				count_env_entries(t_env *env);
void			free_string_array_partial(char **array, int count);

/* EXECUTER/MULTIPLE */
/* pipeline_child.c */
void			execute_pipeline_child(t_shell *shell, t_command *cmd);

/* pipeline_external.c */
void			execute_external_in_pipeline(t_shell *shell, t_command *cmd);

/* pipeline.c */
void			setup_pipeline_child(t_command *cmd, int **pipes,
					int cmd_count, int cmd_index);
pid_t			*execute_pipeline_processes(t_shell *shell, int **pipes,
					int cmd_count);
int				**create_pipeline_pipes(int cmd_count);

/* multiple_utils.c */
void			handle_child(t_shell *shell, t_command *cmd, int **pipes,
					int i);
int				skip_empty_command(pid_t *pids, t_command **cmd, int i);
int				handle_pipe_error(int **pipes, int i);

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
char			*extract_quoted_string(char *input, int *i);
char			*extract_word_until_delimiter(char *input, int *i);
char			*extract_operator(char *input, int *i);

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
void			free_pipeline(t_pipeline *pipeline);
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

void		print_shell_info(t_shell *shell);

#endif

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
# include "../libft/libft.h"
# include "defines.h"
# include "structs.h"

/* Global Variable */
extern int	g_sigint_received;

/* Functions */

/* SIGNAL */
/* signals.c */
int			handle_signal_and_exit(t_shell *shell, char **command);
void		check_and_warn(int ret, const char *msg);
void		handle_sigint(int signo);
void		sigint_received(t_shell *shell);

/* signals_2.c */
void		heredoc_signal_handler(int signo);

/* MAIN */
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

/* ERROR */
/* errors.c */
int			handle_fork_error(int fds[2]);
void		handle_export_error(t_shell *shell, const char *arg);
void		command_not_found_error(t_shell *shell, char *cmd);
void		handle_execve_error(char *cmd);

/* CLEANUP_TOOLS */
/* free.c */
void		cleanup_previous_state(t_shell *shell);
void		free_at_exit(t_shell *shell);

/* free_env.c */
void		free_env_list(t_env *env);
void		free_env_node(t_env *node);

/* free_pipeline.c */
void		free_pipeline(t_pipeline *pipeline);
void		free_token_array(t_token *tokens);

/* free_command.c */
void		free_command_list(t_command *commands);
void		free_single_command(t_command *command);
void		free_string_array(char **array);

/* close_fds.c */
void		close_command_fds(t_command *cmd);
void		close_all_command_fds(t_shell *shell);

/* free_builtins.c */
void	cleanup_cd_memory(char *old_pwd, char *target_dir);

/* EXECUTER */
/* executer.c */
void		executer(t_shell *shell);

/* utils.c */
int			ft_strcmp(const char *s1, const char *s2);

/* redirections.c */
int			setup_file_descriptors(t_shell *shell);
int			setup_command_fds(t_command *cmd);
int			setup_output_redirection(t_command *cmd);
int			setup_input_redirection(t_command *cmd);

/* single_command.c */
void		execute_single_command(t_shell *shell, t_command *cmd);

/* multiple_command.c */
void		execute_pipeline_commands(t_shell *shell, int cmd_count);

/*	EXECUTER/BUILTINS */
/* builtins_basics.c */
void		execute_builtin_pwd(t_shell *shell, t_command *cmd);
void		execute_builtin_env(t_shell *shell, t_command *cmd);

/* builtins_echo.c */
void		execute_builtin_echo(t_shell *shell, t_command *cmd);
int			is_valid_echo_flag(const char *arg);

/* builtins_exit.c */
void		execute_builtin_exit(t_shell *shell, t_command *cmd);
int			is_valid_number(const char *str);

/* builtins_cd.c */
void		execute_builtin_cd(t_shell *shell, t_command *cmd);
char		*get_target_directory(t_shell *shell, const char *target_path);
char		*get_home_directory(t_shell *shell);
char		*expand_home_path(t_shell *shell, const char *target_path);
int			change_directory_safely(t_shell *shell, char *target_dir, char *old_pwd);

/* builtins_export.c */
void		execute_builtin_export(t_shell *shell, t_command *cmd);
void		print_export_variables(t_env *env);

/* builtins_unset.c */
void		execute_builtin_unset(t_shell *shell, t_command *cmd);
int			is_valid_identifier(const char *str);
int			process_export_arguments(t_shell *shell, const char *arg);
int			process_assignment(t_shell *shell, const char *arg, char *equal_pos);
int			process_mark_for_export(t_shell *shell, const char *key);

/* builtin_utils.c */
int			is_builtin_command(const char *cmd);
void		execute_builtin(t_shell *shell, t_command *cmd);
void		restore_builtin_redirections(int saved_fds[2]);
void		call_builtin_function(t_shell *shell, t_command *cmd);
void		setup_builtin_redirections(t_command *cmd, int saved_fds[2]);

/* builtins_utils2.c */
char		*get_env_value(t_env *env, const char *key);
void		set_env_variable(t_env **env, const char *key, const char *val);
void		update_pwd_env(t_shell *shell, char *old_pwd);
void		remove_env_variable(t_env **env, const char *key);
int			cmd_counter_except_first(t_command *cmd);

/* EXECUTER/COMMAND */
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
int			is_heredoc_delimeter(t_token *token);

/* EXECUTER/HEREDOC */
/* heredoc_handler.c */
int			setup_heredoc_fds(t_command *cmd);

/* heredoc_parent.c */
void		execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid);

/* heredoc_child.c */
void		execute_heredoc_child(t_command *cmd, int fds[2]);
void		handle_heredoc_input(t_command *cmd, int write_fd);
void		process_single_heredoc(char *delimiter, int write_fd);
void		process_single_heredoc_ignore(char *delimiter, int write_fd);

/* EXECUTER/EXTERNAL */
/* external.c */
void		execute_external(t_shell *shell, t_command *cmd);
pid_t		fork_and_execute(t_shell *shell, t_command *cmd, char *exec_path);
void		wait_for_child(t_shell *shell, pid_t pid);

/* path.c */
char		*find_executable_path(t_shell *shell, char *cmd);
char		*check_direct_path(char *cmd);
char		*search_in_path(t_shell *shell, char *cmd);
char		*check_path_directories(char **path_dirs, char *cmd);
char		*build_full_path(char *dir, char *cmd);

/* external_child.c */
void		execute_child_process(t_shell *shell, t_command *cmd, char *exec_path);
char		**convert_env_to_array(t_env *env);
int			count_env_entries(t_env *env);
char		*create_env_string(char *key, char *val);

/* child_utils.c */
int			count_env_entries(t_env *env);
void		free_string_array_partial(char **array, int count);

/* EXECUTER/MULTIPLE */
/* pipeline.c */
int **create_pipeline_pipes(int cmd_count);
pid_t *execute_pipeline_processes(t_shell *shell, int **pipes, int cmd_count);
void setup_pipeline_child(t_command *cmd, int **pipes, int cmd_count, int cmd_index);
void execute_pipeline_child(t_shell *shell, t_command *cmd);
void execute_external_in_pipeline(t_shell *shell, t_command *cmd);
void close_all_pipes_in_child(int **pipes, int cmd_count);
void close_all_pipes_in_parent(int **pipes, int cmd_count);
void cleanup_pipeline(t_shell *shell, int **pipes, pid_t *pids, int cmd_count);
void cleanup_pipes(int **pipes, int cmd_count);
void cleanup_partial_pipes(int **pipes, int created_count);
void cleanup_partial_processes(pid_t *pids, int created_count);

/* ADVANCED LEXER */
/* advanced_lexer.c */
t_token	*advanced_lexer(char *input);
/* advanced_lexer_utils.c */
int		is_whitespace(char c);
int		is_quote(char c);
int		is_redirect_operator(char c);
int		is_pipe(char c);
int		skip_whitespace(char *input, int *i);
/* advanced lexer utils two*/
int				find_quote_end(char *input, int start, char quote_char);
t_token_types	get_advanced_token_type(char *str);
char			*extract_quoted_string(char *input, int *i);
char			*extract_word_until_delimiter(char *input, int *i);
char			*extract_operator(char *input, int *i);

/* REDIRECTS CHECK */
/* redirects Check */
int		check_redirects(t_token *tokens);

/* EOF CHECK*/
/* eof_check */
void	mark_eof_tokens(t_token *tokens);

/* IMPROVED EXPANDER */
/* improved_expander.c */
void	improved_expand_tokens(t_token *tokens, t_env *env);
/* improved_expander_utils.c */
int	is_valid_var_char(char c);
char	*extract_var_name(char *str, int start, int *end);
char	*get_var_value(char *var_name, t_env *env);

/* LEXER */
/* lexer.c */
t_token	*lexer(char *input);
void	free_token_array(t_token *tokens);
void	add_token_to_list(t_token **head, t_token *new_token);
/* lexer_utils.c */
t_token	*create_token(char *content, t_token_types type);

/* PARSER */
/* parser.c */
t_command	*parser(t_token *tokens);
/* parser_utils.c */
void		free_commands(t_command *cmd_list);

/* PIPELINE TOKENIZER */
/* pipeline_tokenizer.c */
t_pipeline	*split_by_pipes(t_token *tokens);
void		free_pipeline(t_pipeline *pipeline);
/* pipeline_tokenizer_utils.c*/
void	fill_pipeline_segments(t_pipeline *pipeline, t_token *tokens);

/* POST EXPANDER */
/* post_expander.c */
void	post_expansion_tokenize(t_token **head);
/* post_expander_utils.c*/
char	**split_by_whitespace_respect_quotes(char *str);
/* post_expander_utils_two.c */
int	skip_ws(char *s, int i);

/* QUOTE REMOVER */
/* quote_remover.c */
void	remove_quotes_from_tokens(t_token *tokens);

/* SYNTAX CHECK */
/* Syntax Check */
int		syntax_check(char *input);

/* TOKEN CLASSIFIER */
/* token_classifier.c */
void		classify_pipeline_tokens(t_pipeline *pipeline);

/* UTILS */
/* utils.c */
void		free_array(char **array);

/* mock data creators and printer */
void link_tokens(t_token *tokens[], int count);
void print_shell_info(t_shell *shell);
const char *get_token_type_name(t_token_types type);
void print_commands_only(t_shell *shell);

/* mock data combinations */
/* echo */
t_pipeline *test_echo_no_args();
t_pipeline *test_echo_hello();
t_pipeline *test_echo_hello_world();
t_pipeline *test_echo_n_hello();
t_pipeline *test_echo_nn_hello();
t_pipeline *test_echo_multiple_n_flags();
t_pipeline *test_echo_invalid_flag();
t_pipeline *test_echo_flag_middle();
t_pipeline *test_echo_consecutive_n_flags();
t_pipeline *test_echo_valid_then_invalid_flag();
t_pipeline *test_echo_redirect_output();
t_pipeline *test_echo_n_append();

/* pwd */
t_pipeline *test_pwd_basic();
t_pipeline *test_pwd_with_arg();
t_pipeline *test_pwd_redirect_output();
t_pipeline *test_pwd_append();

/* env */
t_pipeline *test_env_basic();
t_pipeline *test_env_with_arg();
t_pipeline *test_env_redirect_output();
t_pipeline *test_env_append();
t_pipeline *test_env_pipe();	// henüz yapılmadı

/* exit */
t_pipeline *test_exit_no_arg();
t_pipeline *test_exit_zero();
t_pipeline *test_exit_forty_two();
t_pipeline *test_exit_modulo();
t_pipeline *test_exit_negative();
t_pipeline *test_exit_invalid();
t_pipeline *test_exit_too_many_args();
t_pipeline *test_exit_positive_sign();
t_pipeline *test_exit_partial_invalid();

/* cd */
t_pipeline *test_cd_home();
t_pipeline *test_cd_tilde();
t_pipeline *test_cd_parent();
t_pipeline *test_cd_current();
t_pipeline *test_cd_absolute();
t_pipeline *test_cd_home_path();
t_pipeline *test_cd_nonexistent();
t_pipeline *test_cd_too_many_args();
t_pipeline *test_cd_relative();

/* unset */
t_pipeline *test_unset_no_args();
t_pipeline *test_unset_single_var();
t_pipeline *test_unset_multiple_vars();
t_pipeline *test_unset_path();
t_pipeline *test_unset_home();
t_pipeline *test_unset_pwd();
t_pipeline *test_unset_nonexistent_var();
t_pipeline *test_unset_invalid_name_number();
t_pipeline *test_unset_invalid_name_hyphen();
t_pipeline *test_unset_invalid_name_special();
t_pipeline *test_unset_valid_underscore();
t_pipeline *test_unset_valid_with_numbers();
t_pipeline *test_unset_shell();
t_pipeline *test_unset_mixed_validity();
t_pipeline *test_unset_empty_string();
void setup_test_environment(t_shell *shell);

/* export */
t_pipeline *test_export_no_args();
t_pipeline *test_export_new_var();
t_pipeline *test_export_modify_existing();
t_pipeline *test_export_existing_var();
t_pipeline *test_export_nonexistent_var();
t_pipeline *test_export_empty_value();
t_pipeline *test_export_quoted_value();
t_pipeline *test_export_multiple_vars();
t_pipeline *test_export_invalid_name_number();
t_pipeline *test_export_invalid_name_hyphen();
t_pipeline *test_export_invalid_name_special();
t_pipeline *test_export_valid_underscore();
t_pipeline *test_export_valid_with_numbers();
t_pipeline *test_export_value_with_equals();
t_pipeline *test_export_just_equals();
t_pipeline *test_export_no_name();
t_pipeline *test_export_empty_string();
t_pipeline *test_export_mixed_validity();
t_pipeline *test_export_override_home();
t_pipeline *test_export_override_pwd();
void setup_export_test_environment(t_shell *shell);

/* external test cases */
t_pipeline *test_ls_basic();
t_pipeline *test_ls_with_flags();
t_pipeline *test_ls_with_directory();
t_pipeline *test_absolute_path_command();
t_pipeline *test_relative_path_command();
t_pipeline *test_pwd_command();
t_pipeline *test_cat_with_file();
t_pipeline *test_grep_with_pattern();
t_pipeline *test_whoami_command();
t_pipeline *test_date_command();
t_pipeline *test_wc_line_count();
t_pipeline *test_command_not_found();
t_pipeline *test_absolute_path_not_found();
t_pipeline *test_relative_path_not_found();
t_pipeline *test_ls_permission_directory();
t_pipeline *test_sleep_command();
t_pipeline *test_env_command();
t_pipeline *test_absolute_echo_with_args();

/* heredoc */
t_pipeline *test_heredoc_basic();
t_pipeline *test_heredoc_custom_delimiter();
t_pipeline *test_heredoc_delimiter_with_numbers();
t_pipeline *test_heredoc_delimiter_underscore();
t_pipeline *test_heredoc_with_grep();
t_pipeline *test_heredoc_with_wc();
t_pipeline *test_heredoc_with_file();
t_pipeline *test_heredoc_quoted_delimiter();
t_pipeline *test_heredoc_single_quoted_delimiter();
t_pipeline *test_heredoc_single_char_delimiter();
t_pipeline *test_heredoc_long_delimiter();
t_pipeline *test_heredoc_with_command_flags();
t_pipeline *test_heredoc_with_sort();
t_pipeline *test_heredoc_with_head();
t_pipeline *test_heredoc_with_tr();
t_pipeline *test_multiple_heredocs_cat();
t_pipeline *test_multiple_heredocs_grep();
t_pipeline *test_triple_heredocs();
t_pipeline *test_multiple_heredocs_sort();
t_pipeline *test_heredocs_with_file_mixed();
t_pipeline *test_multiple_heredocs_head();
t_pipeline *test_multiple_heredocs_tr();
t_pipeline *test_same_delimiter_multiple();
t_pipeline *test_multiple_heredocs_uniq();
t_pipeline *test_quadruple_heredocs();

/* redirections */
/* output redirection '>' */
t_pipeline *test_output_redirection_basic();
t_pipeline *test_output_redirection_ls();
t_pipeline *test_output_redirection_absolute_path();
t_pipeline *test_output_redirection_overwrite();

/* append redirection '>>' */
t_pipeline *test_append_redirection_basic();
t_pipeline *test_append_redirection_ls();
t_pipeline *test_append_redirection_absolute();

/* input redirection '<' */
t_pipeline *test_input_redirection_basic();
t_pipeline *test_input_redirection_wc();
t_pipeline *test_input_redirection_absolute();
t_pipeline *test_input_redirection_grep();

/* combined */
t_pipeline *test_combined_input_output();
t_pipeline *test_combined_input_append();
t_pipeline *test_combined_grep_redirections();

/* multiple output/append/input redirections */
t_pipeline *test_multiple_output_redirections();
t_pipeline *test_multiple_append_redirections();
t_pipeline *test_multiple_input_redirections();

/* with heredoc */
t_pipeline *test_heredoc_with_output();
t_pipeline *test_heredoc_with_append();

/* error cases */
t_pipeline *test_output_permission_denied();
t_pipeline *test_input_file_not_found();
t_pipeline *test_output_to_dev_null();

/* more complex */
t_pipeline *test_complex_multiple_redirections();
t_pipeline *test_flags_with_redirections();
t_pipeline *test_complex_command_redirections();

/* pipelines */
/* basics */
t_pipeline *test_pipeline_basic();
t_pipeline *test_pipeline_filter();
t_pipeline *test_pipeline_count_lines();

/* three-command pipes */
t_pipeline *test_pipeline_three_commands();
t_pipeline *test_pipeline_sort_limit();

/* long pipes */
t_pipeline *test_pipeline_long_chain();

/* with builtins */
t_pipeline *test_pipeline_builtin_to_external();
t_pipeline *test_pipeline_external_to_builtin();

/* with redirections */
t_pipeline *test_pipeline_with_output_redirect();
t_pipeline *test_pipeline_with_input_redirect();

/* with heredoc */
t_pipeline *test_pipeline_with_heredoc();

/* complex */
t_pipeline *test_pipeline_complex_combination();

/* error cases */
t_pipeline *test_pipeline_error_first_command();
t_pipeline *test_pipeline_error_second_command();
t_pipeline *test_pipeline_error_last_command();

#endif
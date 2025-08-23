#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H

#include "../structs.h"

/*	EXECUTER/BUILTINS */
/* builtins_basics.c */
void			execute_builtin_pwd(t_shell *shell, t_command *cmd);
void			execute_builtin_env(t_shell *shell, t_command *cmd);

/* builtins_cd.c */
int				change_directory_safely(t_shell *shell, char *target_dir,
					char *old_pwd);
char			*expand_home_path(t_shell *shell, const char *target_path);
char			*get_home_directory(t_shell *shell);
char			*get_target_directory(t_shell *shell, const char *target_path);
void			execute_builtin_cd(t_shell *shell, t_command *cmd);

/* builtins_echo.c */
int				is_dollar_question_mark(t_shell *shell, const char *arg);
int				is_valid_echo_flag(const char *arg);
void			execute_builtin_echo(t_shell *shell, t_command *cmd);

/* builtins_exit.c */
int				is_valid_number(const char *str);
void			execute_builtin_exit(t_shell *shell, t_command *cmd);

/* builtins_export_utils.c */
int				is_valid_identifier_export(const char *str);
int				count_env_keys(t_env *env);
void			copy_env_to_array(t_env *env, t_env **array);
void			sort_env_array(t_env **array, int size);

/* builtins_export.c */
int				process_mark_for_export(t_shell *shell, const char *key);
int				process_assignment(t_shell *shell, const char *arg,
					char *equal_pos);
int				process_export_arguments(t_shell *shell, const char *arg);
void			print_export_variables(t_env *env);
void			execute_builtin_export(t_shell *shell, t_command *cmd);

/* builtins_unset.c */
int	            is_valid_flag_unset(t_shell *shell, char *cmd);
void			execute_builtin_unset(t_shell *shell, t_command *cmd);

/* builtin_utils.c */
int				is_builtin_command(const char *cmd);
void			setup_builtin_redirections(t_command *cmd, int saved_fds[2]);
void			call_builtin_function(t_shell *shell, t_command *cmd);
void			restore_builtin_redirections(int saved_fds[2]);
void			execute_builtin(t_shell *shell, t_command *cmd);

/* builtins_utils2.c */
int				cmd_counter_except_first(t_command *cmd);
void			remove_env_variable(t_env **env, const char *key);
void			set_env_variable(t_env **env, const char *key, const char *val);
char			*get_env_value(t_env *env, const char *key);
void			update_pwd_env(t_shell *shell, char *old_pwd);

#endif // MINISHELL_BUILTINS_H

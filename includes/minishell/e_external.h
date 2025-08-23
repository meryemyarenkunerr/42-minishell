#ifndef MINISHELL_EXTERNAL_H
#define MINISHELL_EXTERNAL_H

#include "../structs.h"

/* EXECUTER/EXTERNAL */

/* child_utils.c */
void			free_string_array_partial(char **array, int count);
int				count_env_entries(t_env *env);

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
char			*create_env_string(char *key, char *val);
char			**convert_env_to_array(t_env *env);
void			execute_child_process(t_shell *shell, t_command *cmd,
					char *exec_path);

#endif // MINISHELL_EXTERNAL_H

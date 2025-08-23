#ifndef MINISHELL_MAIN_H
#define MINISHELL_MAIN_H

#include "../structs.h"
#include "../defines.h"

/* init_env.c */
void			add_new_env_node(t_env **env, t_env *tail);
t_env			*create_env_node_empty(void);
t_env			*create_env_node(char *key, char *val);
int				extract_key_value(char *env_pair, char **key, char **val);
int				add_key_value_pair(t_env **env, char *env_pair);

/* init.c */
void			init_simple_signal(int signo);
void			init_signal(void);
t_env			*init_env(char **env);
void			init_shell(t_shell *shell, char **env);

/* process_command.c */
void			process_command(t_shell *shell, char *command);

/* prompt.c */
char			*build_prompt(void);

/* shell_loop.c */
int				is_exit(t_shell *shell);
void			shell_loop(t_shell *shell);

#endif

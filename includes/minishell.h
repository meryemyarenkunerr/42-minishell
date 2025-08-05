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
void	init_shell(t_shell *shell, char **env);

/* env_utils.c */
t_env	*init_env(char **env);

/* free.c */
void	free_env_list(t_env *env);
void	free_at_exit(t_shell *shell);

/* shell_loop.c */
void	shell_loop(t_shell *shell);

/* signals.c */
void	setup_signal_handler(struct termios *term_backup);

/* prompt_utils.c */
void	build_prompt(t_shell *shell);

#endif
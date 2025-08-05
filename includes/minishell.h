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

/* Own Headers */
# include <../libft/libft.h>
# include "defines.h"
# include "structs.h"

/* Functions */
/* init_shell.c */
void	init_shell(t_shell *mini, char **env);

/* init_env.c */


/* utils.c */


#endif
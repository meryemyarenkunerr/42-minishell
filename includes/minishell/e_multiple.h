#ifndef MINISHELL_MULTIPLE_H
#define MINISHELL_MULTIPLE_H

#include "../structs.h"

/* EXECUTER/MULTIPLE */

/* multiple_command.c */
void	execute_multiple_commands(t_shell *shell, int cmd_count);

/* pipeline_child.c */
void	execute_pipeline_child(t_shell *shell, t_command *cmd,
	int **pipes, int idx);

/* pipeline_utils.c */
void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx,
	int cmd_count);
void	wait_pipeline_processes(t_shell * shell, t_command *cmds,
	int cmd_count);

#endif

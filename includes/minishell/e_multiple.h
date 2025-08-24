#ifndef MINISHELL_MULTIPLE_H
#define MINISHELL_MULTIPLE_H

#include "../structs.h"

/* EXECUTER/MULTIPLE */

/* multiple_utils.c */
void			handle_child(t_shell *shell, t_command *cmd, int **pipes,
					int i);
int				skip_empty_command(pid_t *pids, t_command **cmd, t_pipeline_ctx *ctx);
int				handle_pipe_error(int **pipes, int i);

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

#endif

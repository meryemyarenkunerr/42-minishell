#ifndef MINISHELL_CLEANUP_H
#define MINISHELL_CLEANUP_H

#include "../structs.h"

/* CLEANUP_TOOLS */
/* close_fds.c */
void			close_command_fds(t_command *cmd);
void			close_all_command_fds(t_shell *shell);

/* close_pipes.c */
void			close_all_pipes_in_child(int **pipes, int cmd_count);
void			close_all_pipes_in_parent(int **pipes, int cmd_count);

/* free_builtins.c */
void			cleanup_cd_memory(char *old_pwd, char *target_dir);

/* free_command.c */
void			free_string_array(char **array);
void			free_single_command(t_command *command);
void			free_command_list(t_command *commands);
int				cleanup_and_return_error(t_shell *shell);

/* free_env.c */
void			free_env_node(t_env *node);
void			free_env_list(t_env *env);

/* free_heredoc.c */
void			complete_cleanup_and_exit(t_shell *shell, int exit_code);

/* free_pipeline.c */
void			free_token_array(t_token *tokens);
void			free_pipeline(t_pipeline *pipeline);

/* free_pipes.c */
void	cleanup_pipes(int **pipes, int count);
void	close_all_pipe_fds(int **pipes, int count);
void	close_remaining_pipe_fds(int **pipes, int pipe_count, int curr_idx);

/* free.c */
void			free_at_exit(t_shell *shell);
void			cleanup_previous_state(t_shell *shell);

#endif

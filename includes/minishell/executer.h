#ifndef MINISHELL_EXECUTER_H
#define MINISHELL_EXECUTER_H

#include "../structs.h"

/* EXECUTER */
/* executer.c */
void			executer(t_shell *shell);

/* multiple_command.c */
void			execute_pipeline_commands(t_shell *shell, int cmd_count);

/* redirections.c */
int				setup_command_fds(t_shell *shell, t_command *cmd);
int				setup_file_descriptors(t_shell *shell);

/* single_command.c */
void			execute_single_command(t_shell *shell, t_command *cmd);

/* utils.c */
int				ft_strcmp(const char *s1, const char *s2);
int				open_output_file(t_shell *shell, t_command *cmd, int i);
void			close_old_fd(int *fd_out);
int				is_input_file(t_command *cmd, char *filename);
int				is_output_file(t_command *cmd, char *filename);

/* utils2.c */
int				setup_single_input_file(t_shell *shell, t_command *cmd, char *filename);
int				setup_single_output_file(t_shell *shell, t_command *cmd, char *filename, int append_mode);

#endif // MINISHELL_EXECUTER_H

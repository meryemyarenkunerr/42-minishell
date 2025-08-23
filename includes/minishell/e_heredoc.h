#ifndef MINISHELL_HEREDOC_H
#define MINISHELL_HEREDOC_H

#include "../structs.h"

/* EXECUTER/HEREDOC */
/* heredoc_child.c */
void			process_single_heredoc_ignore(char *delimiter, int write_fd);
void			process_single_heredoc(t_shell *shell, char *delimiter,
					int write_fd);
void			handle_heredoc_input(t_shell *shell, t_command *cmd,
					int write_fd);
void			execute_heredoc_child(t_shell *shell, t_command *cmd,
					int fds[2]);

/* heredoc_handler.c */
int				setup_heredoc_fds(t_shell *shell, t_command *cmd);

/* heredoc_parent.c */
void			execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid);

/* heredoc_utils.c */
int				is_heredoc_interrupted(void);
int				check_line_conditions(char *line, char *delimiter);
char			*process_line_content(t_shell *shell, char *line);
void			write_processed_line(int write_fd, char *processed_line);

#endif // MINISHELL_HEREDOC_H

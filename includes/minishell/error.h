#ifndef MINISHELL_ERROR_H
#define MINISHELL_ERROR_H

#include "../structs.h"

/* ERROR */
/* builtins_error.c */
void			ft_exit(t_shell *shell, t_command *cmd);
void			numeric_argument_error_exit(t_shell *shell, t_command *cmd);
void			too_many_argument_error_exit(t_shell *shell, t_command *cmd);

/* errors.c */
void			handle_export_error(t_shell *shell, char *arg);
int				handle_fork_error(int fds[2]);
pid_t			*handle_fork_error_multiple(pid_t *pids, int i);
void			command_not_found_error(t_shell *shell, char *cmd);
void			handle_execve_error(char *cmd);

/* heredoc_error.c */
void			print_eof_warning(char *delimiter);
void			print_file_error(char *filename, char *error_msg);

/* syntax_error.c */
void			redirects_error(char *text, t_shell *shell);
void			quote_error(void);

#endif

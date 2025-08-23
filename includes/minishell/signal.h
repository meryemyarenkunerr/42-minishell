#ifndef MINISHELL_SIGNAL_H
#define MINISHELL_SIGNAL_H

#include "../structs.h"

int handle_signal_and_exit(t_shell *shell, char **command);
void check_and_warn(int ret, const char *msg);
void handle_sigint(int signo);
void sigint_received(t_shell *shell);
void heredoc_signal_handler(int signo);

#endif // MINISHELL_SIGNAL_H

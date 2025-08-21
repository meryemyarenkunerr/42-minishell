#include "../../includes/minishell.h"

void print_eof_warning(char *delimiter)
{
	write(STDERR_FILENO, "\nminishell: warning: here-document delimited by ", 48);
	write(STDERR_FILENO, "end-of-file (wanted `", 21);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", 3);
}
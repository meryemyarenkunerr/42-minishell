#include "../../includes/minishell.h"

void	print_eof_warning(char *delimiter)
{
	ft_putstr_fd("\nminishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by ", STDERR_FILENO);
	ft_putstr_fd("end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

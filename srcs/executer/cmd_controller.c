#include "../../includes/minishell.h"

// kontrol fonksiyonları
int	is_input_redirection(const char *arg)
{
	return (ft_strncmp(arg, REDIRECTION_IN, 1) == 0 && arg[1] == '\0');
}

int	is_output_redirection(const char *arg)
{
	return (ft_strncmp(arg, REDIRECTION_OUT, 1) == 0 && arg[1] == '\0');
}

int	is_appended_redirection(const char *arg)
{
	return (ft_strncmp(arg, REDIRECTION_APPEND, 2) == 0);
}

int	is_heredoc_redirection(const char *arg)
{
	return (ft_strncmp(arg, REDIRECTION_HEREDOC, 2) == 0);
}
#include "../../includes/minishell.h"

// kontrol fonksiyonları
int	is_input_redirection(const char *arg)
{
	return (ft_strcmp(arg, REDIRECTION_IN) == 0 && arg[1] == '\0');
}

int	is_output_redirection(const char *arg)
{
	return (ft_strcmp(arg, REDIRECTION_OUT) == 0 && arg[1] == '\0');
}

int	is_appended_redirection(const char *arg)
{
	return (ft_strcmp(arg, REDIRECTION_APPEND) == 0);
}

int	is_heredoc_redirection(const char *arg)
{
	return (ft_strcmp(arg, REDIRECTION_HEREDOC) == 0);
}
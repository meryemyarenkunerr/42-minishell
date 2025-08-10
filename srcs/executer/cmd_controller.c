#include "../../includes/minishell.h"

// kontrol fonksiyonları
int	is_input_redirection(const char *arg)
{
	return (ft_strncmp(arg, "<", 1) == 0 && arg[1] == '\0');
}

int	is_output_redirection(const char *arg)
{
	return (ft_strncmp(arg, ">", 1) == 0 && arg[1] == '\0');
}

int	is_appended_redirection(const char *arg)
{
	return (ft_strncmp(arg, ">>", 2) == 0);
}
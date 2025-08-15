#include "../../includes/minishell.h"

static int is_number(const char *s)
{
	if (!*s) // boş string
		return 0;
	if (*s == '+' || *s == '-') // işaret kontrolü
		s++;
	if (!*s) // sadece + veya - varsa geçersiz
		return 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return 0;
		s++;
	}
	return 1;
}

int	is_exit_command_received(t_shell *shell, char *command)
{
	char	*stat;

	if (ft_strcmp(command, EXIT) == 0 &&
		(command[4] == '\0' || command[4] == ' '))
	{
		printf("bye bye <3\n");
		if (command[4] == ' ') // status değeri var
		{
			stat = command + 5;
			if (!is_number(stat))
			{
				printf("minishell: exit: %s: numeric argument required\n", stat);
				shell->exit_status = 255;
			}
			else
				shell->exit_status = ft_atoi(stat);
		}
		return TRUE;
	}
	return FALSE;
}

char	*read_line(t_shell *shell)
{
	char	*command;
	char	*temp;

	if (isatty(fileno(stdin)))
	{
		command = readline(shell->prompt);
		if (!command)
			return NULL;
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			free(command);
			return (ft_strdup(""));
		}
	}
	else
	{
		temp = get_next_line(fileno(stdin));
		if (!temp)
			return (NULL);
		command = ft_strtrim(temp, "\n");
		free(temp);
		if (!command)
			return NULL;
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			free(command);
			return (ft_strdup(""));
		}
	}
	return (command);
}
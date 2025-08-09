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

	if (ft_strncmp(command, EXIT, 4) == 0 &&
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

void	sigint_received(t_shell *shell)
{
	shell->exit_status = 130; // POSIX standardı (Ctrl+C için)
	g_sigint_received = FALSE;
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
	}
	return (command);
}
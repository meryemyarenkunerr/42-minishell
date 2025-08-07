#include "../includes/minishell.h"

int	process_command(t_shell *shell, char *command)
{
	t_token		*tokens;
	t_command	*cmd_list;

	if (*command == '\0') // enter'a basılmışsa
		return TRUE;
	tokens = advanced_lexer(command);
	if (tokens)
	{
		improved_expand_tokens(tokens, shell->environment); // Use improved expander
		remove_quotes_from_tokens(tokens); // Remove quotes FIRST
		post_expansion_tokenize(&tokens); // Then re-tokenize
		cmd_list = parser(tokens);
		if (cmd_list)
		{
			// executer bölümü
			free_commands(cmd_list);
		}
		free_tokens(tokens);
		add_history(command);
	}
	return TRUE;
}

char	*read_line(t_shell *shell)
{
	char	*command;
	char	*temp;

	if (isatty(fileno(stdin)))
	{
		if (!shell->prompt)
			shell->prompt = ft_strdup(PROMPT);
		command = readline(shell->prompt);
	}
	else
	{
		temp = get_next_line(fileno(stdin));
		if (!temp)
			return (NULL);
		command = ft_strtrim(temp, "\n");
		free(temp);
	}
	return (command);
}

void	shell_loop(t_shell *shell)
{
	char		*command;

	while (1)
	{
		setup_signal_handler(&shell->term_backup); // sinyal işlemleri ve terminal ayarı
		build_prompt(shell); // prompt'un dinamik bir şekilde oluşturulması
		command = read_line(shell);
		printf("Komut: %s\n", command);
		if (!command) // Ctrl-D veya EOF
		{
			printf("bye bye <3\n");
			break ;
		}
		if (g_sigint_received) // Ctrl+C ile komut iptal edildiyse
		{
			shell->exit_status = 130; // POSIX standardı (Ctrl+C için)
			g_sigint_received = FALSE;
			free(command);
			continue ; // döngü devam etmeli
		}
		if (!process_command(shell, command))
			break ;
		free(command);
	}
}
#include "../includes/minishell.h"

int	process_command(t_shell *shell, char *command)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (*command == '\0') // enter'a basılmışsa
		return TRUE;
	tokens = NULL;
	shell->commands = NULL;
	pipeline = NULL;
	tokens = advanced_lexer(command);
	if (tokens)
	{
		improved_expand_tokens(tokens, shell->environment); // Use improved expander
		remove_quotes_from_tokens(tokens); // Remove quotes FIRST
		post_expansion_tokenize(&tokens); // Then re-tokenize
		pipeline = split_by_pipes(tokens);
		if (pipeline)
		{
			classify_pipeline_tokens(pipeline);
			shell->commands = parser(tokens);
			if (shell->commands)
			{
				// executer(shell, pipeline, tokens, cmd_list);
				free_commands(shell->commands);
			}
			free_pipeline(pipeline);
		}
		free_tokens(tokens);
		add_history(command);
	}
	// şimdilik executer'ı burada başlatıyorum
	tokens = build_token_list();
	pipeline = split_pipeline(tokens);
	shell->commands = build_commands(pipeline);
	executer(shell, pipeline, tokens);
	free_commands_temp(shell->commands);
	free_pipeline_temp(pipeline);
	free_token_list_temp(tokens);
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
		// printf("Komut: %s\n", command);
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
#include "../../includes/minishell.h"

t_pipeline	*process_input(char *input, t_env *envlist)
{
	t_token		*tokens;
	t_pipeline	*pipeline;
	int			hata;

	hata = 0;
	if (!input || !*input)
		return (NULL);
	if (!syntax_check(input))
		hata = 1;
	tokens = advanced_lexer(input);
	if (!tokens)
		return (NULL);
	mark_eof_tokens(tokens);
	improved_expand_tokens(tokens, envlist);
	post_expansion_tokenize(&tokens);
	remove_quotes_from_tokens(tokens);
	if (!check_redirects(tokens))
		hata = 2;
	pipeline = split_by_pipes(tokens);
	if (!pipeline)
	{
		hata = 3;
		free_token_array(tokens);
		return (NULL);
	}
	classify_pipeline_tokens(pipeline);


	if (hata == 1)
		printf("❌ ❌ ❌Tırnak hatasssııı \n ");
	else if (hata == 2)
		printf("❌ ❌ ❌ Heredoc heredoc yan yana heredoc hatasssııı \n ");
	else if (hata == 3)
		printf("❌ ❌ ❌ pipline parçalanamadı hatasssııı \n ");

	// Cleanup
	free_token_array(tokens);

	return (pipeline);
}

void	process_command(t_shell *shell, char *command)
{
	if (!shell || !command)
		return ;

	cleanup_previous_state(shell);
	shell->pipeline = process_input(command, shell->environment);
	if (!builds_commands_from_pipeline(shell))
		return ;
	if (!setup_file_descriptors(shell))
		return ;
	//print_shell_info(shell);
	executer(shell);
}

#include "../includes/minishell.h"

void	build_prompt(t_shell *shell)
{
	char	*cwd;
	char	*temp;
	char	*combined;

	// önceki prompt'u temizle
	if (shell->prompt)
		free(shell->prompt);

	// dizini al
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		shell->prompt = ft_strdup(PROMPT);
		return ;
	}
	temp = ft_strjoin(PROMPT_WO_DOLLAR, cwd);
	combined = ft_strjoin(temp, DOLLAR_SIGN);

	free(cwd);
	free(temp);
	shell->prompt = combined;
	shell->cmd_has_been_executed = TRUE;
}
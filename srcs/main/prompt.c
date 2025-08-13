#include "../../includes/minishell.h"

static void	update_current_dir_before_command(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (shell->current_dir)
			free(shell->current_dir);
		shell->current_dir = ft_strdup(cwd);
		free(cwd);
	}
}

void	build_prompt(t_shell *shell)
{
	char	*temp;
	char	*colored_path;

	update_current_dir_before_command(shell);
	if (shell->prompt)
		free(shell->prompt);
	if (!shell->current_dir)
	{
		shell->prompt = ft_strdup(PROMPT);
		return ;
	}
	colored_path = ft_strjoin(BLUE, shell->current_dir);
	temp = ft_strjoin(colored_path, RESET DOLLAR_SIGN);
	free(colored_path);
	shell->prompt = ft_strjoin(PROMPT_WO_DOLLAR, temp);
	free(temp);
	shell->cmd_has_been_executed = TRUE;
}
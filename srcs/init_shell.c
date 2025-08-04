#include "../includes/minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return NULL;
}

void	init_shell(t_shell *mini, char **env)
{
	// set environemnt variables
	mini->env = NULL;
	mini->env_head = init_env(env);
	mini->cmd_paths = ft_split(get_path(env), ':');
	mini->user_name = getenv("USER");

	// set state flags
	mini->exit_code = 0;
	mini->cmd_has_been_executed = TRUE;
	mini->print = FALSE;
	mini->color_codes = TRUE;

	// set command and prompt info
	mini->terminal_prompt = NULL;
	mini->commands = NULL;

	// set heredoc
	mini->heredoc_temp = NULL;
	// mini->expand_heredoc = NULL;

	// set input and output
	mini->std_fds[0] = dup(STDIN);
	mini->std_fds[1] = dup(STDOUT);
}
#include "../../../includes/minishell.h"

void	execute_external_in_pipeline(t_shell *shell, t_command *cmd)
{
	char	**env_array;
	char	*executable_path;

	executable_path = find_executable_path(shell, cmd->cmd);
	if (!executable_path)
	{
		printf("minishell: %s: command not found\n", cmd->cmd);
		exit(127);
	}
	env_array = convert_env_to_array(shell->environment);
	if (!env_array)
	{
		free(executable_path);
		exit(127);
	}
	if (execve(executable_path, cmd->arguments, env_array) == -1)
	{
		handle_execve_error(cmd->cmd);
		free_string_array(env_array);
		free(executable_path);
		exit(127);
	}
}

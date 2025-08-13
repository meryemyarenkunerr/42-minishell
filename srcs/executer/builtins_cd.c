#include "../../includes/minishell.h"

static int	update_current_dir(t_shell *shell)
{
	char	*new_dir;

	new_dir = getcwd(NULL, 0);
	if(!new_dir)
	{
		perror("getcwd");
		return FALSE;
	}
	free(shell->current_dir);
	shell->current_dir = new_dir;
	return TRUE;
}

static char	*get_cd_path(t_shell *shell, t_command *cmd)
{
	if (!cmd->arguments[1])
		return (shell->home_dir);
	else
		return (cmd->arguments[1]);
}

void	execute_builtin_cd(t_shell *shell, t_command *cmd)
{
	char	*path;

	path = get_cd_path(shell, cmd);
	if (!path)
	{
		printf("cd: HOME not set\n");
		shell->exit_status = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return ;
	}
	if (!update_current_dir(shell))
	{
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
}
#include "../../../includes/minishell.h"

int	change_directory_safely(t_shell *shell, char *target_dir, char *old_pwd)
{
	if (chdir(target_dir) == -1)
	{
		perror("minishell: cd");
		shell->exit_status = 1;
		cleanup_cd_memory(old_pwd, target_dir);
		return (FALSE);
	}
	return (TRUE);
}

char	*expand_home_path(t_shell *shell, const char *target_path)
{
	char	*home_dir;
	char	*target;

	home_dir = get_env_value(shell->environment, "HOME");
	if (!home_dir)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	if (target_path[1] == '\0')
		return (ft_strdup(home_dir));
	if (target_path[1] == '/')
	{
		target = ft_strjoin(home_dir, target_path + 1);
		return (target);
	}
	return (ft_strdup(target_path));
}

char	*get_home_directory(t_shell *shell)
{
	char	*home_dir;

	home_dir = get_env_value(shell->environment, "HOME");
	if (!home_dir)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (ft_strdup(home_dir));
}

char	*get_target_directory(t_shell *shell, const char *target_path)
{
	if (!target_path)
		return (get_home_directory(shell));
	if (target_path[0] == '~')
		return (expand_home_path(shell, target_path));
	return (ft_strdup(target_path));
}

void	execute_builtin_cd(t_shell *shell, t_command *cmd)
{
	char	*target_dir;
	char	*old_pwd;
	int		cmd_count;

	cmd_count = cmd_counter_except_first(cmd);
	if (cmd_count > 1)
	{
		printf("minishell: cd: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	target_dir = get_target_directory(shell, cmd->arguments[1]);
	if (!target_dir)
	{
		shell->exit_status = 1;
		cleanup_cd_memory(old_pwd, NULL);
		return ;
	}
	if (!change_directory_safely(shell, target_dir, old_pwd))
		return ;
	update_pwd_env(shell, old_pwd);
	shell->exit_status = 0;
	cleanup_cd_memory(old_pwd, target_dir);
}

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);  // veya hata handling

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin_command(const char *cmd)
{
	if (!cmd)
		return FALSE;
	if (ft_strcmp(cmd, "cd") == 0)
		return TRUE;
	if (ft_strcmp(cmd, "echo") == 0)
		return TRUE;
	if (ft_strcmp(cmd, "env") == 0)
		return TRUE;
	if (ft_strcmp(cmd, "export") == 0)
		return TRUE;
	if (ft_strcmp(cmd, "pwd") == 0)
		return TRUE;
	if (ft_strcmp(cmd, "unset") == 0)
		return TRUE;
	return FALSE;
}

void	execute_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		execute_builtin_cd(shell, cmd);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		execute_builtin_echo(shell, cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		execute_builtin_env(shell, cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		execute_builtin_export(shell, cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		execute_builtin_pwd(shell, cmd);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		execute_builtin_unset(shell, cmd);
}
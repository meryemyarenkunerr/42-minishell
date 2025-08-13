#include "../../includes/minishell.h"

void	execute_builtin_pwd(t_shell *shell, t_command *cmd)
{
	(void)cmd;
	if (shell->current_dir)
	{
		printf("%s\n", shell->current_dir);
		shell->exit_status = 0;
	}
	else
	{
		perror("pwd");
		shell->exit_status = 1;
	}
}

void	execute_builtin_echo(t_shell *shell, t_command *cmd)
{
	int	i;
	int	new_line;

	i = 1;			// 0 -> echo
	new_line = 1;	// \n eklenecek mi kontrolü
	if (cmd->arguments && cmd->arguments[1] &&
		ft_strcmp(cmd->arguments[1], "-n") == 0)
	{
		new_line = 0;
		i = 2;		// -n'i atlamak için
	}
	while (cmd->arguments && cmd->arguments[i])
	{
		printf("%s", cmd->arguments[i]);
		if (cmd->arguments[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	shell->exit_status = 0;
}

void	execute_builtin_env(t_shell *shell, t_command *cmd)
{
	t_env	*curr;
	(void)cmd;

	curr = shell->environment;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	shell->exit_status = 0;
}
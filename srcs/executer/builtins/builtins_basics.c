#include "../../../includes/minishell.h"

void	execute_builtin_pwd(t_shell *shell, t_command *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		shell->exit_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	shell->exit_status = 0;
}

void	execute_builtin_env(t_shell *shell, t_command *cmd)
{
	t_env	*curr;

	(void)cmd;
	if (!shell->environment)
	{
		shell->exit_status = 0;
		return ;
	}
	curr = shell->environment;
	while (curr)
	{
		if (curr->key && curr->value)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	shell->exit_status = 0;
}
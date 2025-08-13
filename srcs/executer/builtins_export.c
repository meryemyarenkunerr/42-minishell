#include "../../includes/minishell.h"

static void	print_export_format(t_shell *shell)
{
	t_env	*curr;

	curr = shell->environment;
	while (curr)
	{
		if (curr->value == NULL)
			printf("declare -x %s\n", curr->key);
		else if (ft_strlen(curr->value) == 0)
			printf("declare -x %s=\"\"\n", curr->key);
		else
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		curr = curr->next;
	}
}

static void	mark_variable_exported(t_shell *shell, const char *key)
{
	t_env	*existing;

	existing = find_env_variable(shell->environment, key);
	if (!existing)
		add_env_variable(shell, key, NULL);
}

static void	process_export_arg(t_shell *shell, const char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		set_env_variable(shell, arg);
	else
		mark_variable_exported(shell, arg);
	shell->exit_status = 0;
}

static int	validate_export_arg(const char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
		return FALSE;
	if (arg[0] == '=')
		return FALSE;
	if (ft_isdigit(arg[0]))
		return FALSE;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return FALSE;
	return TRUE;
}

void	execute_builtin_export(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd->arguments[1])
	{
		print_export_format(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd->arguments[i])
	{
		if (validate_export_arg(cmd->arguments[i]))
			process_export_arg(shell, cmd->arguments[i]);
		else
			handle_export_error(shell, cmd->arguments[i]);
		i++;
	}
}
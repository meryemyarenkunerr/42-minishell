#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env	*create_new_env_node(char *env_entry)
{
	t_env	*node;
	size_t	key_len;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	value = ft_strchr(env_entry, '=');
	if (!value)
	{
		free(node);
		return (NULL);
	}
	key_len = value - env_entry;
	node->key = ft_strndup(env_entry, key_len);
	node->value = ft_strdup(value + 1);
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;

	head = NULL;
	tail = NULL;
	while (*env)
	{
		new = create_new_env_node(*env);
		if (!new)
		{
			free_env_list(head);
			return (NULL);
		}
		if (!head)
		{
			head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}
		env++;
	}
	return (head);
}

void	init_shell(t_shell *shell, char **env)
{
	char	*home;

	shell->cmd_has_been_executed = TRUE; // sorun çıkmasın başlangıçta diye
	shell->commands = NULL;
	shell->current_dir = getcwd(NULL, 0);	// malloc ile alan açar, freele
	if (!shell->current_dir)
		shell->current_dir = ft_strdup("");
	shell->environment = init_env(env);
	shell->exit_status = 0;
	home = getenv("HOME");
	if (home)
		shell->home_dir = ft_strdup(home);	// freelenmeli
	else
		shell->home_dir = NULL;
	shell->prompt = NULL;
	if (tcgetattr(STDIN_FILENO, &shell->term_backup) == -1)
		perror("tcgetattr");
}
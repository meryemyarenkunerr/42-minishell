/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 19:48:31 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char **env)
{
	t_env	*head;
	int		i;

	head = NULL;
	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!add_key_value_pair(&head, env[i]))
		{
			free_env_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

void	init_shell(t_shell *shell, char **env)
{
	if (!shell)
		return ;
	shell->environment = init_env(env);
	shell->exit_status = 0;
	shell->exit = 0;
	shell->commands = NULL;
	shell->pipeline = NULL;
	handle_signals();
}

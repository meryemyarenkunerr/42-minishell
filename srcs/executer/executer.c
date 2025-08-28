/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:32:48 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:32:49 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executer(t_shell *shell)
{
	if (!shell || !shell->pipeline)
		return ;
	if (shell->pipeline->count == 1)
		execute_single_command(shell, shell->commands);
	else
		execute_multiple_commands(shell, shell->pipeline->count);
}

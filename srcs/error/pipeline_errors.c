/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:34:24 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:34:26 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipes_creation_error(t_shell *shell)
{
	ft_putstr_fd("minishell: failed to create pipes\n", STDERR_FILENO);
	shell->exit_status = 1;
}

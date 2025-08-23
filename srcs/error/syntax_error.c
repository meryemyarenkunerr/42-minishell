/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:16:27 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 18:10:26 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirects_error(char *text, t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
	ft_putstr_fd("near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(text, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	shell->exit_status = 2;
}

void	quote_error(void)
{
	ft_putstr_fd("minishell: unexpected end of file while", STDERR_FILENO);
	ft_putstr_fd(" looking for matching quote\n", STDERR_FILENO);
}

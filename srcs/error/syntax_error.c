/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:16:27 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/22 00:39:11 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirects_error(char *text, t_shell *shell)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, text, strlen(text));
	write(2, "'\n", 2);
	shell->exit_status = 2;
}

void	quote_error(void)
{
	write(2, "minishell: unexpected end of file while", 39);
	write(2, " looking for matching quote\n", 28);
}

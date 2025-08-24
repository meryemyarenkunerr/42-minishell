/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:35:22 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_prompt(void)
{
	char	*cwd;
	char	*colored_path;
	char	*temp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(PROMPT));
	colored_path = ft_strjoin(BLUE, cwd);
	temp = ft_strjoin(colored_path, RESET DOLLAR_SIGN);
	prompt = ft_strjoin(GREEN PROMPT_WO_DOLLAR RESET, temp);
	free(cwd);
	free(colored_path);
	free(temp);
	return (prompt);
}

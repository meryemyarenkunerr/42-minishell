/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improved_expander_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:21:14 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:09:21 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_var_name(char *str, int start, int *end)
{
	int		i;
	char	*var_name;
	int		len;

	i = start;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	*end = i;
	len = i - start;
	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + start, len + 1);
	return (var_name);
}

char	*get_var_value(char *var_name, t_env *env)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	value = get_env_value(env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*append_exit_status(char *result, t_shell *shell, int *i)
{
	char	*var_value;
	char	*temp;

	var_value = ft_itoa(shell->exit_status);
	temp = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	*i = *i + 2;
	return (temp);
}

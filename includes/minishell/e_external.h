/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_external.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:29:31 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:29:33 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_EXTERNAL_H
# define E_EXTERNAL_H

# include "../structs.h"

int		count_env_entries(t_env *env);
void	free_string_array_partial(char **array, int count);
void	execute_child_process(t_shell *shell, t_command *cmd,
			char *exec_path);
void	execute_external(t_shell *shell, t_command *cmd);
char	*current_directory(t_shell *shell, char *cmd);
char	*find_executable_path(t_shell *shell, char *cmd);

#endif

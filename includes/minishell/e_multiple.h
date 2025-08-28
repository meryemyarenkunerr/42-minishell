/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_multiple.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:29:45 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:29:47 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_MULTIPLE_H
# define E_MULTIPLE_H

# include "../structs.h"

void	execute_multiple_commands(t_shell *shell, int cmd_count);
int		**create_pipeline_pipes(int pipe_count);
void	execute_pipeline_child(t_shell *shell, t_command *cmd,
			int **pipes, int idx);
void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx,
			int cmd_count);
char	**get_env_array(t_env *environment);
char	*resolve_command_path(t_shell *shell, t_command *cmd,
			char **env_array, int **pipes);
void	wait_pipeline_processes(t_shell *shell, t_command *cmds,
			int cmd_count);

#endif

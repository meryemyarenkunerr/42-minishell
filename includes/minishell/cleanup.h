/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 15:31:56 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "../structs.h"

void	close_command_fds(t_command *cmd);
void	cleanup_cd_memory(char *old_pwd, char *target_dir);
int		cleanup_and_return_error(t_shell *shell);
void	free_command_list(t_command *commands);
void	free_string_array(char **array);
void	free_env_list(t_env *env);
void	free_env_node(t_env *node);
void	free_pipeline(t_pipeline *pipeline);
void	free_token_array(t_token *tokens);
void	close_remaining_pipe_fds(int **pipes, int pipe_count, int curr_idx);
void	close_all_pipe_fds(int **pipes, int count);
void	cleanup_pipes(int **pipes, int count);
void	cleanup_previous_state(t_shell *shell);
void	free_at_exit(t_shell *shell);
void	partial_cleanup_fds(int **pipes, int cmd_count, int idx);

#endif

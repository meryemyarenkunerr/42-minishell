/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 15:14:20 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_pipes(int **pipes, int count)
{
       int i;
       
       if (!pipes)
	       return;
       
       i = 0;
       while (i < count)
       {
	       if (pipes[i])
	       {
		       if (pipes[i][0] >= 0)
		       {
			       close(pipes[i][0]);
			       pipes[i][0] = -1;
		       }
		       if (pipes[i][1] >= 0)
		       {
			       close(pipes[i][1]);
			       pipes[i][1] = -1;
		       }
		       free(pipes[i]);
	       }
	       i++;
       }
       free(pipes);
}

void	close_all_pipe_fds(int **pipes, int count)
{
       int i;
       
       if (!pipes)
	       return;
       
       i = 0;
       while (i < count)
       {
	       if (pipes[i])
	       {
		       if (pipes[i][0] >= 0)
		       {
			       close(pipes[i][0]);
			       pipes[i][0] = -1;
		       }
		       if (pipes[i][1] >= 0)
		       {
			       close(pipes[i][1]);
			       pipes[i][1] = -1;
		       }
	       }
	       i++;
       }
}

void	close_remaining_pipe_fds(int **pipes, int pipe_count, int curr_idx)
{
	int i;

	if (!pipes)
		return;
	
	i = 0;
	while (i < pipe_count) {
		// Sadece curr_idx-1 ve curr_idx pipe'ları açık bırak
		if (i != curr_idx - 1 && i != curr_idx) {
			if (pipes[i]) {
				if (pipes[i][0] >= 0)
				{
					close(pipes[i][0]);
					pipes[i][0] = -1;
				}
				if (pipes[i][1] >= 0)
				{
					close(pipes[i][1]);
					pipes[i][1] = -1;
				}
			}
		}
		i++;
	}
}
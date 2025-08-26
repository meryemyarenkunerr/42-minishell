/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 14:15:48 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_pipes(int **pipes, int count)
{
       int i;
       
       ft_putstr_fd("\nDEBUG PIPES: cleanup_pipes called with count=", STDERR_FILENO);
       ft_putnbr_fd(count, STDERR_FILENO);
       ft_putstr_fd("\n", STDERR_FILENO);
       
       if (!pipes)
       {
              ft_putstr_fd("DEBUG PIPES: NULL pipes array, returning\n", STDERR_FILENO);
	       return;
       }
       
       i = 0;
       while (i < count)
       {
	       if (pipes[i])
	       {
		       ft_putstr_fd("DEBUG PIPES: Closing pipe ", STDERR_FILENO);
		       ft_putnbr_fd(i, STDERR_FILENO);
		       ft_putstr_fd(" read(", STDERR_FILENO);
		       ft_putnbr_fd(pipes[i][0], STDERR_FILENO);
		       ft_putstr_fd(") write(", STDERR_FILENO);
		       ft_putnbr_fd(pipes[i][1], STDERR_FILENO);
		       ft_putstr_fd(")\n", STDERR_FILENO);
		       
		       close(pipes[i][0]);
		       close(pipes[i][1]);
		       free(pipes[i]);
	       }
	       i++;
       }
       free(pipes);
       ft_putstr_fd("DEBUG PIPES: cleanup_pipes completed\n", STDERR_FILENO);
}

void	close_all_pipe_fds(int **pipes, int count)
{
       int i;
       
       ft_putstr_fd("\nDEBUG PIPES: close_all_pipe_fds called with count=", STDERR_FILENO);
       ft_putnbr_fd(count, STDERR_FILENO);
       ft_putstr_fd("\n", STDERR_FILENO);
       
       if (!pipes)
       {
              ft_putstr_fd("DEBUG PIPES: NULL pipes array, returning\n", STDERR_FILENO);
	       return;
       }
       
       i = 0;
       while (i < count)
       {
	       if (pipes[i])
	       {
		       ft_putstr_fd("DEBUG PIPES: Closing pipe ", STDERR_FILENO);
		       ft_putnbr_fd(i, STDERR_FILENO);
		       ft_putstr_fd(" read(", STDERR_FILENO);
		       ft_putnbr_fd(pipes[i][0], STDERR_FILENO);
		       ft_putstr_fd(") write(", STDERR_FILENO);
		       ft_putnbr_fd(pipes[i][1], STDERR_FILENO);
		       ft_putstr_fd(")\n", STDERR_FILENO);
		       
		       // Ayrı ayrı kapatma işlemlerini debug için izleyelim
		       if (close(pipes[i][0]) == -1)
		           ft_putstr_fd("DEBUG PIPES: Error closing read end\n", STDERR_FILENO);
		       else
		           ft_putstr_fd("DEBUG PIPES: Successfully closed read end\n", STDERR_FILENO);
		           
		       if (close(pipes[i][1]) == -1)
		           ft_putstr_fd("DEBUG PIPES: Error closing write end\n", STDERR_FILENO);
		       else
		           ft_putstr_fd("DEBUG PIPES: Successfully closed write end\n", STDERR_FILENO);
	       }
	       i++;
       }
       ft_putstr_fd("DEBUG PIPES: close_all_pipe_fds completed\n", STDERR_FILENO);
}

void	close_remaining_pipe_fds(int **pipes, int pipe_count, int curr_idx)
{
	int i;

	ft_putstr_fd("\nDEBUG PIPES: close_remaining_pipe_fds called with pipe_count=", STDERR_FILENO);
	ft_putnbr_fd(pipe_count, STDERR_FILENO);
	ft_putstr_fd(", curr_idx=", STDERR_FILENO);
	ft_putnbr_fd(curr_idx, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	if (!pipes)
	{
		ft_putstr_fd("DEBUG PIPES: NULL pipes array, returning\n", STDERR_FILENO);
		return;
	}
	
	i = 0;
	while (i < pipe_count) {
		// Sadece curr_idx-1 ve curr_idx pipe'ları açık bırak
		if (i != curr_idx - 1 && i != curr_idx) {
			if (pipes[i]) {
				ft_putstr_fd("DEBUG PIPES: Closing pipe ", STDERR_FILENO);
				ft_putnbr_fd(i, STDERR_FILENO);
				ft_putstr_fd(" read(", STDERR_FILENO);
				ft_putnbr_fd(pipes[i][0], STDERR_FILENO);
				ft_putstr_fd(") write(", STDERR_FILENO);
				ft_putnbr_fd(pipes[i][1], STDERR_FILENO);
				ft_putstr_fd(")\n", STDERR_FILENO);
				
				if (close(pipes[i][0]) == -1)
				    ft_putstr_fd("DEBUG PIPES: Error closing read end\n", STDERR_FILENO);
				else
				    ft_putstr_fd("DEBUG PIPES: Successfully closed read end\n", STDERR_FILENO);
				    
				if (close(pipes[i][1]) == -1)
				    ft_putstr_fd("DEBUG PIPES: Error closing write end\n", STDERR_FILENO);
				else
				    ft_putstr_fd("DEBUG PIPES: Successfully closed write end\n", STDERR_FILENO);
			}
		}
		else {
			ft_putstr_fd("DEBUG PIPES: Keeping pipe ", STDERR_FILENO);
			ft_putnbr_fd(i, STDERR_FILENO);
			ft_putstr_fd(" open for current command\n", STDERR_FILENO);
		}
		i++;
	}
	ft_putstr_fd("DEBUG PIPES: close_remaining_pipe_fds completed\n", STDERR_FILENO);
}
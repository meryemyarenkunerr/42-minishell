/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 21:32:22 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes_in_child(int **pipes, int cmd_count)
{
	int i = 0;
    int pipe_count = cmd_count - 1;

    while (i < pipe_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void	close_all_pipes_in_parent(int **pipes, int cmd_count)
{
	int i = 0;
    int pipe_count = cmd_count - 1;

    while (i < pipe_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

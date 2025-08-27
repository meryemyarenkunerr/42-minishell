/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:06:21 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	*allocate_pipe_fds(void)
{
	int	*fds;

	fds = malloc(2 * sizeof(int));
	if (!fds)
		return (NULL);
	fds[0] = -1;
	fds[1] = -1;
	if (pipe(fds) == -1)
	{
		perror("pipe");
		free(fds);
		return (NULL);
	}
	return (fds);
}

int	**create_pipeline_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	pipes = malloc(pipe_count * sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = allocate_pipe_fds();
		if (!pipes[i])
		{
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

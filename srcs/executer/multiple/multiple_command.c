/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 14:22:33 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	**create_pipeline_pipes(int pipe_count)
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
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
void	execute_multiple_commands(t_shell *shell, int cmd_count)
{
	t_command	*cmd;
	int			**pipes;
	int			i;

	ft_putstr_fd("\nDEBUG EXEC: Starting execute_multiple_commands with cmd_count=", STDERR_FILENO);
	ft_putnbr_fd(cmd_count, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	if (!shell || !shell->commands)
	{
		ft_putstr_fd("DEBUG EXEC: Invalid shell or commands\n", STDERR_FILENO);
		return ;
	}
	
	pipes = create_pipeline_pipes(cmd_count - 1);  // pipelar oluşturuluyor
	if (!pipes && cmd_count > 1)
	{
		ft_putstr_fd("DEBUG EXEC: Failed to create pipes\n", STDERR_FILENO);
		pipes_creation_error(shell);
		return ;
	}
	
	ft_putstr_fd("DEBUG EXEC: Pipes created successfully\n", STDERR_FILENO);
	
	cmd = shell->commands;
	i = 0;
	while (i < cmd_count && cmd) // her bir komutun üzerinden geçilir
	{
		ft_putstr_fd("DEBUG EXEC: Forking for command ", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putstr_fd(" (", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
		
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			ft_putstr_fd("DEBUG EXEC: Fork failed\n", STDERR_FILENO);
			perror("fork");
			shell->exit_status = 1;
			break ;
		}
		
		if (cmd->pid == 0) // child
		{
			ft_putstr_fd("DEBUG EXEC: Child process started for command ", STDERR_FILENO);
			ft_putstr_fd(cmd->cmd, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			execute_pipeline_child(shell, cmd, pipes, i);
			// Bu noktaya hiç ulaşılmamalı, çünkü execute_pipeline_child _exit ile çıkış yapar
			ft_putstr_fd("DEBUG EXEC: Child process DID NOT exit properly!\n", STDERR_FILENO);
			_exit(1);
		}
		
		// Parent süreçte, mevcut komut için artık gerekli olmayan pipe uçlarını kapat
		if (i > 0 && pipes)
		{
			// Önceki pipe'ın okuma ucunu kapat (artık gerekli değil)
			ft_putstr_fd("DEBUG EXEC: Parent closing read end of previous pipe\n", STDERR_FILENO);
			if (close(pipes[i-1][0]) == -1)
				ft_putstr_fd("DEBUG EXEC: Error closing read end in parent\n", STDERR_FILENO);
			else
				ft_putstr_fd("DEBUG EXEC: Successfully closed read end in parent\n", STDERR_FILENO);
		}
		
		if (i < cmd_count - 1 && pipes)
		{
			// Mevcut pipe'ın yazma ucunu kapat (artık gerekli değil)
			ft_putstr_fd("DEBUG EXEC: Parent closing write end of current pipe\n", STDERR_FILENO);
			if (close(pipes[i][1]) == -1)
				ft_putstr_fd("DEBUG EXEC: Error closing write end in parent\n", STDERR_FILENO);
			else
				ft_putstr_fd("DEBUG EXEC: Successfully closed write end in parent\n", STDERR_FILENO);
		}
		
		ft_putstr_fd("DEBUG EXEC: Parent continues, child PID=", STDERR_FILENO);
		ft_putnbr_fd(cmd->pid, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		
		cmd = cmd->next;
		i++;
	}
	
	ft_putstr_fd("DEBUG EXEC: All children forked, now closing all pipes in parent\n", STDERR_FILENO);
	// Parent process'te her koşulda tüm pipe'ları kapat
	if (pipes)
	{
		ft_putstr_fd("DEBUG EXEC: Calling close_all_pipe_fds in parent\n", STDERR_FILENO);
		close_all_pipe_fds(pipes, cmd_count - 1);
	}
	
	ft_putstr_fd("DEBUG EXEC: All pipes closed in parent, now waiting for children\n", STDERR_FILENO);
	wait_pipeline_processes(shell, shell->commands, cmd_count);
	
	ft_putstr_fd("DEBUG EXEC: All children finished, cleanup pipes\n", STDERR_FILENO);
	if (pipes)
	{
		ft_putstr_fd("DEBUG EXEC: Calling cleanup_pipes in parent\n", STDERR_FILENO);
		cleanup_pipes(pipes, cmd_count - 1);
	}
	
	ft_putstr_fd("DEBUG EXEC: execute_multiple_commands completed\n", STDERR_FILENO);
}

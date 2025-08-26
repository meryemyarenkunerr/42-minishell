/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 14:22:33 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_pipeline_processes(t_shell * shell, t_command *cmds, int cmd_count)
{
	int			i;
	int			last_exit_status;
	t_command	*cmd;
	int			status;
	int			exit_code;

	ft_putstr_fd("\nDEBUG WAIT: Waiting for processes, cmd_count=", STDERR_FILENO);
	ft_putnbr_fd(cmd_count, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	i = 0;
	last_exit_status = 0;
	cmd = cmds;
	while (i < cmd_count && cmd)
	{
		ft_putstr_fd("DEBUG WAIT: Processing command ", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putstr_fd(" (", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
		ft_putstr_fd("), PID=", STDERR_FILENO);
		ft_putnbr_fd(cmd->pid, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		
		if (cmd->pid > 0)
		{
			ft_putstr_fd("DEBUG WAIT: Waiting for PID ", STDERR_FILENO);
			ft_putnbr_fd(cmd->pid, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			
			// Önce WNOHANG ile deneyelim
			int ret = waitpid(cmd->pid, &status, WNOHANG);
			if (ret == 0) {
				ft_putstr_fd("DEBUG WAIT: Process still running, waiting with block...\n", STDERR_FILENO);
				waitpid(cmd->pid, &status, 0);
			}
			
			ft_putstr_fd("DEBUG WAIT: Process PID ", STDERR_FILENO);
			ft_putnbr_fd(cmd->pid, STDERR_FILENO);
			ft_putstr_fd(" finished with status ", STDERR_FILENO);
			ft_putnbr_fd(status, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				ft_putstr_fd("DEBUG WAIT: Process exited normally with code ", STDERR_FILENO);
				ft_putnbr_fd(exit_code, STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				
				if (i == cmd_count - 1)
					last_exit_status = exit_code;
			}
			else if (WIFSIGNALED(status))
			{
				ft_putstr_fd("DEBUG WAIT: Process terminated by signal ", STDERR_FILENO);
				ft_putnbr_fd(WTERMSIG(status), STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				
				if (i == cmd_count - 1)
					last_exit_status = 128 + WTERMSIG(status);
			}
			else
			{
				ft_putstr_fd("DEBUG WAIT: Process neither exited normally nor by signal\n", STDERR_FILENO);
			}
		}
		else
		{
			ft_putstr_fd("DEBUG WAIT: Skipping command with invalid PID\n", STDERR_FILENO);
		}
		
		cmd = cmd->next;
		i++;
	}
	
	ft_putstr_fd("DEBUG WAIT: All processes done, final exit_status=", STDERR_FILENO);
	ft_putnbr_fd(last_exit_status, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	shell->exit_status = last_exit_status;
}

void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{	
	ft_putstr_fd("\nDEBUG SETUP: setup_pipeline_fds called for command: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(", idx=", STDERR_FILENO);
	ft_putnbr_fd(idx, STDERR_FILENO);
	ft_putstr_fd(", cmd_count=", STDERR_FILENO);
	ft_putnbr_fd(cmd_count, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	// Her durumda pipe'ın uçlarını dup2 ile yönlendir
	if (idx > 0)
	{
		ft_putstr_fd("DEBUG SETUP: Setting up input pipe from previous command\n", STDERR_FILENO);
		// Pipe'ın okuma ucunu stdin'e yönlendir
		cmd->fd_in = pipes[idx - 1][0]; // Önce fd'yi kaydet
		
		ft_putstr_fd("DEBUG SETUP: Redirecting STDIN to pipe[", STDERR_FILENO);
		ft_putnbr_fd(idx - 1, STDERR_FILENO);
		ft_putstr_fd("][0] (fd=", STDERR_FILENO);
		ft_putnbr_fd(pipes[idx - 1][0], STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
		
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
		{
			ft_putstr_fd("DEBUG SETUP: dup2 pipe input failed\n", STDERR_FILENO);
			perror("dup2 pipe input");
		}
		
		ft_putstr_fd("DEBUG SETUP: Closing original pipe read end\n", STDERR_FILENO);
		if (close(pipes[idx - 1][0]) == -1)
		    ft_putstr_fd("DEBUG SETUP: Error closing read end\n", STDERR_FILENO);
		else
		    ft_putstr_fd("DEBUG SETUP: Successfully closed read end\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("DEBUG SETUP: First command, no input pipe\n", STDERR_FILENO);
	}
	
	if (idx < cmd_count - 1)
	{
		ft_putstr_fd("DEBUG SETUP: Setting up output pipe to next command\n", STDERR_FILENO);
		// Pipe'ın yazma ucunu stdout'a yönlendir
		cmd->fd_out = pipes[idx][1]; // Önce fd'yi kaydet
		
		ft_putstr_fd("DEBUG SETUP: Redirecting STDOUT to pipe[", STDERR_FILENO);
		ft_putnbr_fd(idx, STDERR_FILENO);
		ft_putstr_fd("][1] (fd=", STDERR_FILENO);
		ft_putnbr_fd(pipes[idx][1], STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
		
		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("DEBUG SETUP: dup2 pipe output failed\n", STDERR_FILENO);
			perror("dup2 pipe output");
		}
		
		ft_putstr_fd("DEBUG SETUP: Closing original pipe write end\n", STDERR_FILENO);
		if (close(pipes[idx][1]) == -1)
		    ft_putstr_fd("DEBUG SETUP: Error closing write end\n", STDERR_FILENO);
		else
		    ft_putstr_fd("DEBUG SETUP: Successfully closed write end\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("DEBUG SETUP: Last command, no output pipe\n", STDERR_FILENO);
	}
	
	ft_putstr_fd("DEBUG SETUP: Closing remaining pipes\n", STDERR_FILENO);
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
	
	ft_putstr_fd("DEBUG SETUP: setup_pipeline_fds completed\n", STDERR_FILENO);
}

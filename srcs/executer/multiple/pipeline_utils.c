/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 18:10:33 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_pipeline_processes(t_shell * shell, t_command *cmds, int cmd_count)
{
	int			i;
	int			last_exit_status;
	t_command	*cmd;
	int			status;
	int			completed[256] = {0}; // Tamamlanan process'leri izlemek için
	int			remaining = cmd_count;
	pid_t		last_completed_pid = -1;
	
	i = 0;
	last_exit_status = 0;
	cmd = cmds;
	
	// Process'leri kaydedelim
	t_command *all_cmds[256] = {0};
	i = 0;
	cmd = cmds;
	while (i < cmd_count && cmd)
	{
		all_cmds[i] = cmd;
		i++;
		cmd = cmd->next;
	}
	
	// İlk olarak WNOHANG ile kontrol edelim - hızlı bitenleri yakalayalım
	for (int loop = 0; loop < 2 && remaining > 0; loop++)
	{
		i = 0;
		while (i < cmd_count)
		{
			if (!completed[i] && all_cmds[i] && all_cmds[i]->pid > 0)
			{
				pid_t pid = all_cmds[i]->pid;
				if (waitpid(pid, &status, WNOHANG) > 0)
				{
					completed[i] = 1;
					remaining--;
					
					// Son process ise exit status'u kaydet
					if (i == cmd_count - 1)
					{
						if (WIFEXITED(status))
							last_exit_status = WEXITSTATUS(status);
						else if (WIFSIGNALED(status))
							last_exit_status = 128 + WTERMSIG(status);
					}
				}
			}
			i++;
		}
	}
	
	// Hala kalan process varsa, normal waitpid ile bekleyelim
	while (remaining > 0)
	{
		// Herhangi bir child process için waitpid çağrısı yap
		pid_t finished_pid = waitpid(-1, &status, 0);
		if (finished_pid <= 0)
			break;
		
		last_completed_pid = finished_pid;
		
		// Hangi process'in tamamlandığını bul
		i = 0;
		int found_idx = -1;
		while (i < cmd_count)
		{
			if (all_cmds[i] && all_cmds[i]->pid == finished_pid)
			{
				completed[i] = 1;
				found_idx = i;
				break;
			}
			i++;
		}
		
		// Son process ise exit status'u kaydet
		if (found_idx == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
		
		remaining--;
		
		// Eğer son process tamamlandıysa, kalan process'leri sonlandır
		if (found_idx == cmd_count - 1 && remaining > 0)
		{
			// Kalan process'leri sonlandır
			i = 0;
			while (i < cmd_count)
			{
				if (!completed[i] && all_cmds[i] && all_cmds[i]->pid > 0)
				{
					kill(all_cmds[i]->pid, SIGTERM);
					// Hemen waitpid ile bekleyelim, zombi process olmasın
					waitpid(all_cmds[i]->pid, NULL, 0);
					completed[i] = 1;
					remaining--;
				}
				i++;
			}
		}
	}
	
	// Herhangi bir kalan process var mı?
	i = 0;
	while (i < cmd_count)
	{
		if (!completed[i] && all_cmds[i] && all_cmds[i]->pid > 0)
		{
			kill(all_cmds[i]->pid, SIGTERM);
			waitpid(all_cmds[i]->pid, NULL, 0);
		}
		i++;
	}
	
	shell->exit_status = last_exit_status;
}

void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{	
	// Aşağıdaki mantık sırasıyla işlem yapalım:
	// 1. Komutun özel yönlendirmeleri varsa, bunlar öncelikli
	// 2. Özel yönlendirme yoksa, pipe bağlantıları kullanılır
	// 3. Tüm kullanılmayan pipe uçları kapatılır
	
	// Özel yönlendirmelerin işlenip işlenmediğini takip etmek için değişkenler
	int input_handled = 0;
	int output_handled = 0;
	
	// ÖNEMLİ DÜZELTME: Önce dosya yönlendirmelerini ayarla (redirection)
	
	// 1. Özel giriş yönlendirmesi (örn. <file)
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 3)
	{
		// dup2 ile giriş yönlendirmesini ayarla
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 input redirection");
		// Orijinal fd'yi kapat, artık gerekli değil
		close(cmd->fd_in);
		// İşlendiğini belirt
		input_handled = 1;
	}
	
	// 1. Özel çıkış yönlendirmesi (örn. >file or >>file)
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 3)
	{
		// dup2 ile çıkış yönlendirmesini ayarla
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 output redirection");
		// Orijinal fd'yi kapat, artık gerekli değil
		close(cmd->fd_out);
		// İşlendiğini belirt
		output_handled = 1;
		
		// ÖNEMLİ DÜZELTME: Çıkış yönlendirmesi yapıldıysa ve bu pipe'ın ilk veya ortadaki komutu ise,
		// pipe'ın yazma ucunu kapatmalıyız, çünkü artık çıktı dosyaya gidiyor
		// if (idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 3)
		// {
		// 	close(pipes[idx][1]);
		// 	pipes[idx][1] = -1;
		// }
	}
	
	// Ardından pipe'ları ayarlayalım - Eğer dosya yönlendirmesi yapılmadıysa
	// 2. Pipe giriş yönlendirmesi (cmd1 | cmd2 - cmd2 için giriş)
	if (!input_handled && idx > 0 && pipes && pipes[idx - 1] && pipes[idx - 1][0] >= 0)
	{
		// Komut pipe zincirinin ortasında veya sonundaysa,
		// pipe'dan okuma yapacağız
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
			perror("dup2 pipe input");
		
		// Pipe ucu kopyalandı, artık kapatılabilir
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
		input_handled = 1;
	}
	else if (idx > 0 && pipes && pipes[idx - 1] && pipes[idx - 1][0] >= 0)
	{
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
	}
	
	// 2. Pipe çıkış yönlendirmesi (cmd1 | cmd2 - cmd1 için çıkış)
	if (!output_handled && idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 0)
	{
		// Komut pipe zincirinin başında veya ortasındaysa,
		// pipe'a yazma yapacağız
		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
			perror("dup2 pipe output");
		
		// Pipe ucu kopyalandı, artık kapatılabilir
		close(pipes[idx][1]);
		pipes[idx][1] = -1;
		output_handled = 1;
	}
	else if (idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 0)
	{
		close(pipes[idx][1]);
		pipes[idx][1] = -1;
	}
	
	// 3. Kullanılmayan diğer pipe uçlarını kapat
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
}

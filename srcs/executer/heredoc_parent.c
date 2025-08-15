#include "../../includes/minishell.h"

static int	child_killed_by_signal(int status)
{
	return (status != 0 && (status & 0x7F) != 0);
}
static int	get_terminating_signal(int status)
{
	return (status & 0x7F);
}

int	heredoc_parent_process(int fds[2], pid_t pid)
{
	int	status;

	close(fds[1]); // write end'i kapat
	printf("DEBUG: Parent waiting for child %d\n", pid);
	waitpid(pid, &status, 0); // child process'i bekle, status child'ın ne ile döndüğünü bilmek için
	printf("DEBUG: Child finished with status %d\n", status);
	if (child_killed_by_signal(status) && get_terminating_signal(status) == SIGINT) // child'dan Ctrl+C gelirse
	{
		close(fds[0]); // read'i kapat
		g_sigint_received = 0;
		return FALSE;
	}
	return fds[0];
}
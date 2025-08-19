#include "../../includes/minishell.h"

void	cleanup_cd_memory(char *old_pwd, char *target_dir)
{
	if (old_pwd)
		free(old_pwd);
	if (target_dir)
		free(target_dir);
}

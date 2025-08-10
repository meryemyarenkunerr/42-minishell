#include "../../includes/minishell.h"

// setter fonksiyonları
void	set_input_file(t_shell *shell, t_command *cmd, char *file, int *flag)
{
	cmd->input_file = ft_strdup(file);
	if (!cmd->input_file)
	{
		printf("error: malloc failed\n");
		shell->exit_status = 1;
		*flag = FALSE;
		return ;
	}
	*flag = TRUE;
}

void	set_output_file(t_shell *shell, t_command *cmd, char *file, int append, int *flag)
{
	cmd->output_file = ft_strdup(file);
	if (!cmd->output_file)
	{
		printf("error: malloc failed\n");
		shell->exit_status = 1;
		*flag = FALSE;
		return ;
	}
	cmd->append_mode = append;
	*flag = TRUE;
}
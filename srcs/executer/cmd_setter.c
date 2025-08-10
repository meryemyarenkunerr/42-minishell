#include "../../includes/minishell.h"

// setter fonksiyonları
void	set_input_file(t_command *cmd, char *file)
{
	cmd->input_file = ft_strdup(file);
}

void	set_output_file(t_command *cmd, char *file, int append)
{
	cmd->append_mode = append;
	cmd->output_file = ft_strdup(file);
}
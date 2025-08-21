#include "../../../includes/minishell.h"

static int	validate_pipeline(t_shell *shell)
{
	if (!shell || !shell->pipeline || !shell->pipeline->token_lists)
		return (FALSE);
	if (shell->pipeline->count == 0)
		return (FALSE);
	return (TRUE);
}

static void	initialize_command_chain(t_shell *shell)
{
	if (shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
}

static void	link_command_to_chain(t_shell *shell, t_command *cmd, t_command **prev)
{
	if (*prev)
		(*prev)->next = cmd;
	else
		shell->commands = cmd;
	*prev = cmd;
}

static int	process_pipeline_segment(t_shell *shell, int segment_index,
	t_command **prev)
{
	t_command	*curr;
	t_token		*token_list;

	token_list = shell->pipeline->token_lists[segment_index];
	curr = create_command_from_tokens(token_list);
	if (!curr)
	{
		if (*prev)
			return (merge_redirection_to_previous(*prev, token_list));
		else
			return (FALSE);
	}
	link_command_to_chain(shell, curr, prev);
	return (TRUE);
}

int	builds_commands_from_pipeline(t_shell *shell)
{
	int			i;
	t_command	*prev;

	if (!validate_pipeline(shell))
		return (FALSE);
	initialize_command_chain(shell);
	prev = NULL;
	i = 0;
	while (i < shell->pipeline->count)
	{
		if (!process_pipeline_segment(shell, i, &prev))
			return (cleanup_and_return_error(shell));
		i++;
	}
	if (!shell->commands)
		return (FALSE);
	return (TRUE);
}
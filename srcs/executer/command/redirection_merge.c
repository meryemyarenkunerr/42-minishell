#include "../../../includes/minishell.h"

//static void	set_output_file(t_command *cmd, const char *filename, int append_mode)
//{
//	if (cmd->output_file)
//		free(cmd->output_file);
//	cmd->output_file = ft_strdup(filename);
//	cmd->append_mode = append_mode;
//}

//static void	set_input_file(t_command *cmd, const char *filename)
//{
//	if (cmd->input_file)
//		free(cmd->input_file);
//	cmd->input_file = ft_strdup(filename);
//}

//int	merge_redirection_to_previous(t_command *prev_cmd, t_token *redirect_tokens)
//{
//	t_token	*curr;
//	int		is_quoted;

//	if (!prev_cmd || !redirect_tokens)
//		return (FALSE);
//	curr = redirect_tokens;
//	while (curr)
//	{
//		if (curr->type == TOKEN_REDIRECT_OUT && curr->next &&
//			curr->next->type == TOKEN_FILE)
//			set_output_file(prev_cmd, curr->next->content, 0);
//		else if (curr->type == TOKEN_APPEND && curr->next &&
//			curr->next->type == TOKEN_FILE)
//			set_output_file(prev_cmd, curr->next->content, 1);
//		else if (curr->type == TOKEN_REDIRECT_IN && curr->next &&
//			curr->next->type == TOKEN_FILE)
//			set_input_file(prev_cmd, curr->next->content);
//		else if (curr->type == TOKEN_HEREDOC && curr->next &&
//			(curr->next->type == TOKEN_EOF || curr->next->type == TOKEN_EOF_QUOTE))
//		{
//			is_quoted = (curr->next->type == TOKEN_EOF_QUOTE);
//			add_heredoc_delimiter_with_quote(prev_cmd, curr->next->content, is_quoted);
//		}
//		curr = curr->next;
//	}
//	return (TRUE);
//}
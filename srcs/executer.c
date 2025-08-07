#include "../includes/minishell.h"

void	executer(t_shell *shell, t_pipeline *pipeline, t_token *tokens)
{
	(void)shell;
	(void)pipeline;

	// ilk önce redirection hatası var mı diye bakacağız
	// >, >>, <, << bunlardan sonra gelen değişken geçerli bir filename mi?
	if (check_redirection_syntax(shell, tokens))
	{
		shell->exit_status = 258;
		return ;
	}

	// heredoc kontrolü
	// eğer varsa çalıştıracağız
	if (has_heredoc(tokens))
	{
		printf("heredoc var o yüzden buradayız.\n");
		return ;
	}
}


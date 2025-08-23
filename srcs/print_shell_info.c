/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:53:14 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char *get_token_type_name(t_token_types type)
{
	switch (type)
	{
		case TOKEN_NONE:        return "NONE";
		case TOKEN_WORD:        return "WORD";
		case TOKEN_COMMAND:     return "COMMAND";
		case TOKEN_ARGUMENT:    return "ARGUMENT";
		case TOKEN_FILE:        return "FILE";
		case TOKEN_PIPE:        return "PIPE";
		case TOKEN_REDIRECT_IN: return "REDIRECT_IN";
		case TOKEN_REDIRECT_OUT:return "REDIRECT_OUT";
		case TOKEN_APPEND:      return "APPEND";
		case TOKEN_HEREDOC:     return "HEREDOC";
		case TOKEN_EOF:         return "EOF";
		case TOKEN_EOF_QUOTE:   return "EOF_QUOTE";
		default:                return "UNKNOWN";
	}
}

void	print_shell_info(t_shell *shell)
{
	printf("\n==============================================\n");
	printf("           SHELL DEBUG INFO\n");
	printf("==============================================\n");
	if (!shell)
	{
		printf("❌ Shell pointer is NULL\n");
		printf("==============================================\n");
		return;
	}
	printf("📊 Shell Status:\n");
	printf("  exit_status: %d\n", shell->exit_status);
	printf("  exit: %d\n", shell->exit);
	printf("\n");
	printf("🌍 Environment Variables (first 5):\n");
	if (shell->environment)
	{
		t_env *env = shell->environment;
		int count = 0;
		while (env && count < 5)
		{
			printf("  %s=%s\n", env->key ? env->key : "(null)",
					env->value ? env->value : "(null)");
			env = env->next;
			count++;
		}
		if (env)
			printf("  ... (and more)\n");
	}
	else
		printf("  Environment is NULL\n");
	printf("\n");
	printf("🔧 Commands:\n");
	if (!shell->commands)
	{
		printf("  Commands list is NULL\n");
	}
	else
	{
		t_command *cmd = shell->commands;
		int cmd_index = 1;
		while (cmd)
		{
			if (!cmd)
			{
				printf("ERROR: Command %d pointer is NULL!\n", cmd_index);
				break;
			}
			printf("  ┌─ Command %d:\n", cmd_index);
			if (!cmd->cmd)
			{
				printf("  │ cmd: (null) - WARNING: This might cause issues!\n");
			}
			else
			{
				printf("  │ cmd: %s\n", cmd->cmd);
			}
			printf("  │ arguments:");
			if (!cmd->arguments)
			{
				printf(" (null)");
			}
			else
			{
				int i = 0;
				while (cmd->arguments[i])
				{
					printf(" '%s'", cmd->arguments[i]);
					i++;
					if (i > 100)
					{
						printf(" ... (truncated - too many args)");
						break;
					}
				}
			}
			printf("\n");
			printf("  │ input_files (%d): \n", cmd->input_count);
			if (cmd->input_count == 0)
				printf("  | (null)\n");
			else
			{
				for (int i = 0; i < cmd->input_count; i++)
				printf("  │   [%d]: %s\n", i, cmd->input_files[i]);
			}
			printf("  │ output_files (%d): ", cmd->output_count);
			if (cmd->output_count == 0)
				printf("  | (null)\n");
			else
			{
				printf("\n");
				for (int i = 0; i < cmd->output_count; i++)
				printf("  │   [%d]: %s\n", i, cmd->output_files[i]);
			}
			if (cmd->heredoc_count > 0)
			{
				if (!cmd->heredoc_delimiter)
				{
					printf("  │ ERROR: heredoc_count > 0 but heredoc_delimiter is NULL!\n");
				}
				else if (!cmd->quote_flag)
				{
					printf("  │ ERROR: heredoc_count > 0 but quote_flag is NULL!\n");
				}
				else
				{
					printf("  │ heredoc_delimiters (%d):", cmd->heredoc_count);
					int i = 0;
					while (i < cmd->heredoc_count)
					{
						if (cmd->heredoc_delimiter[i])
							printf(" '%s'", cmd->heredoc_delimiter[i]);
						else
							printf(" (null)");
						i++;
						if (i > 10)
						{
							printf(" ... (truncated)");
							break;
						}
					}
					printf("\n");
					printf("  │ quote_flag:");
					printf(" %d", cmd->quote_flag);
					printf("\n");
				}
			}
			else
			{
				printf("  │ heredoc_delimiters: (none)\n");
			}
			printf("  │ fd_in: %d, fd_out: %d\n", cmd->fd_in, cmd->fd_out);
			printf("  │ pid: %d\n", cmd->pid);
			if (cmd->next == cmd)
			{
				printf("ERROR: Command %d points to itself! Breaking to prevent infinite loop\n", cmd_index);
				break;
			}
			printf("  └─────────────────────────\n");
			cmd = cmd->next;
			cmd_index++;
			if (cmd_index > 20)
			{
				printf("ERROR: Too many commands (>20), breaking to prevent infinite loop\n");
				break;
			}
		}
	}
	printf("\n");
	printf("⚡ Pipeline:\n");
	if (!shell->pipeline)
	{
		printf("  Pipeline is NULL\n");
	}
	else
	{
		printf("  Pipeline count: %d\n", shell->pipeline->count);

		int i = 0;
		while (i < shell->pipeline->count)
		{
			printf("  ┌─ Segment %d tokens:\n", i + 1);

			t_token *token = shell->pipeline->token_lists[i];
			if (!token)
			{
				printf("  │ (null tokens)\n");
			}
			else
			{
				while (token && token->prev)
					token = token->prev;

				int token_index = 1;
				while (token)
				{
					const char *type_name = get_token_type_name(token->type);
					printf("  │ Token %d: '%s' [%s]\n",
							token_index, token->content, type_name);
					token = token->next;
					token_index++;
					if (token_index > 50)
					{
						printf("  │ ... (truncated - too many tokens)\n");
						break;
					}
				}
			}
			printf("  └─────────────────────────\n");
			i++;
		}
	}
	printf("\n==============================================\n");
}

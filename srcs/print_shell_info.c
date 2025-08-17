#include "../includes/minishell.h"

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

    // Print Environment (first few entries)
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

    // Print Commands
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
            printf("  ┌─ Command %d:\n", cmd_index);
            printf("  │ cmd: %s\n", cmd->cmd ? cmd->cmd : "(null)");

            // Arguments
            printf("  │ arguments:");
            if (cmd->arguments)
            {
                int i = 0;
                while (cmd->arguments[i])
                {
                    printf(" '%s'", cmd->arguments[i]);
                    i++;
                }
            }
            else
                printf(" (null)");
            printf("\n");

            // Redirections
            printf("  │ input_file: %s\n", cmd->input_file ? cmd->input_file : "(null)");
            printf("  │ output_file: %s\n", cmd->output_file ? cmd->output_file : "(null)");
            printf("  │ append_mode: %d\n", cmd->append_mode);

            // Heredocs
            if (cmd->heredoc_delimiter && cmd->heredoc_count > 0)
            {
                printf("  │ heredoc_delimiters (%d):", cmd->heredoc_count);
                int i = 0;
                while (i < cmd->heredoc_count)
                {
                    printf(" '%s'", cmd->heredoc_delimiter[i]);
                    i++;
                }
                printf("\n");
            }
            else
                printf("  │ heredoc_delimiters: (null)\n");

            // File descriptors
            printf("  │ fd_in: %d, fd_out: %d\n", cmd->fd_in, cmd->fd_out);
            printf("  │ pid: %d\n", cmd->pid);
            printf("  └─────────────────────────\n");

            cmd = cmd->next;
            cmd_index++;
        }
    }
    printf("\n");

    // Print Pipeline
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
                // Find first token
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
                }
            }
            printf("  └─────────────────────────\n");
            i++;
        }
    }

    printf("\n==============================================\n");
}

// Helper function to get token type name for debugging
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
        default:                return "UNKNOWN";
    }
}

// Simplified version for quick debugging
void print_commands_only(t_shell *shell)
{
    if (!shell || !shell->commands)
    {
        printf("No commands to display\n");
        return;
    }

    printf("\n🔧 Quick Commands View:\n");
    t_command *cmd = shell->commands;
    int i = 1;

    while (cmd)
    {
        printf("%d. %s", i, cmd->cmd ? cmd->cmd : "(null)");

        if (cmd->arguments && cmd->arguments[1])
        {
            printf(" (args:");
            int j = 1;
            while (cmd->arguments[j])
            {
                printf(" %s", cmd->arguments[j]);
                j++;
            }
            printf(")");
        }

        if (cmd->input_file)
            printf(" < %s", cmd->input_file);
        if (cmd->output_file)
            printf(" %s %s", cmd->append_mode ? ">>" : ">", cmd->output_file);
        if (cmd->heredoc_count > 0)
            printf(" << heredoc(%d)", cmd->heredoc_count);

        printf("\n");
        cmd = cmd->next;
        i++;
    }
    printf("\n");
}
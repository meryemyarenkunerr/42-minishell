#include "../includes/minishell.h"

// 1. cd (no argument - go to HOME)
t_pipeline *test_cd_home()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("cd", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. cd ~ (explicit HOME)
t_pipeline *test_cd_tilde()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("~", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. cd .. (parent directory)
t_pipeline *test_cd_parent()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("..", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. cd . (current directory)
t_pipeline *test_cd_current()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token(".", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. cd /tmp (absolute path)
t_pipeline *test_cd_absolute()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("/tmp", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. cd ~/Documents (HOME expansion with path)
t_pipeline *test_cd_home_path()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("~/Documents", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. cd nonexistent (error case)
t_pipeline *test_cd_nonexistent()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("nonexistent_directory", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. cd arg1 arg2 (too many arguments)
t_pipeline *test_cd_too_many_args()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("arg1", TOKEN_ARGUMENT);
    tokens[2] = create_token("arg2", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. cd relative_path (relative directory)
t_pipeline *test_cd_relative()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("cd", TOKEN_COMMAND);
    tokens[1] = create_token("relative_dir", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// Environment checker helper
void print_pwd_env(t_shell *shell)
{
    char *pwd = get_env_value(shell->environment, "PWD");
    char *oldpwd = get_env_value(shell->environment, "OLDPWD");

    printf("PWD env: %s\n", pwd ? pwd : "(not set)");
    printf("OLDPWD env: %s\n", oldpwd ? oldpwd : "(not set)");
}
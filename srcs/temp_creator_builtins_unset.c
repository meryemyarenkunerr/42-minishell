#include "../includes/minishell.h"

// 1. unset (no arguments - should show usage or do nothing)
t_pipeline *test_unset_no_args()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("unset", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. unset VAR (unset single variable)
t_pipeline *test_unset_single_var()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("TEST_VAR", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. unset VAR1 VAR2 VAR3 (unset multiple variables)
t_pipeline *test_unset_multiple_vars()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("VAR1", TOKEN_ARGUMENT);
    tokens[2] = create_token("VAR2", TOKEN_ARGUMENT);
    tokens[3] = create_token("VAR3", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. unset PATH (unset critical environment variable)
t_pipeline *test_unset_path()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("PATH", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. unset HOME (unset HOME variable)
t_pipeline *test_unset_home()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("HOME", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. unset PWD (unset current directory variable)
t_pipeline *test_unset_pwd()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("PWD", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. unset NONEXISTENT_VAR (unset variable that doesn't exist)
t_pipeline *test_unset_nonexistent_var()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("NONEXISTENT_VAR", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. unset 123INVALID (invalid variable name - starts with number)
t_pipeline *test_unset_invalid_name_number()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("123INVALID", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. unset INVALID-NAME (invalid variable name - contains hyphen)
t_pipeline *test_unset_invalid_name_hyphen()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("INVALID-NAME", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 10. unset INVALID@NAME (invalid variable name - contains special character)
t_pipeline *test_unset_invalid_name_special()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("INVALID@NAME", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 11. unset _VALID_NAME (valid variable name with underscore)
t_pipeline *test_unset_valid_underscore()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("_VALID_NAME", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 12. unset VALID123 (valid variable name with numbers at the end)
t_pipeline *test_unset_valid_with_numbers()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("VALID123", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 13. unset SHELL (unset shell variable)
t_pipeline *test_unset_shell()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("SHELL", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 14. unset VAR1 INVALID@VAR VAR2 (mix of valid and invalid variables)
t_pipeline *test_unset_mixed_validity()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("VAR1", TOKEN_ARGUMENT);
    tokens[2] = create_token("INVALID@VAR", TOKEN_ARGUMENT);
    tokens[3] = create_token("VAR2", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 15. unset "" (empty string as variable name)
t_pipeline *test_unset_empty_string()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("unset", TOKEN_COMMAND);
    tokens[1] = create_token("", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

void setup_test_environment(t_shell *shell)
{
    // Set up test variables
    set_env_variable(&shell->environment, "TEST_VAR", "test_value");
    set_env_variable(&shell->environment, "VAR1", "value1");
    set_env_variable(&shell->environment, "VAR2", "value2");
    set_env_variable(&shell->environment, "VAR3", "value3");
    set_env_variable(&shell->environment, "_VALID_NAME", "valid_value");
    set_env_variable(&shell->environment, "VALID123", "valid123_value");
}

void print_env_status(t_shell *shell, const char *var_name)
{
    char *value = get_env_value(shell->environment, var_name);
    printf("%s: %s\n", var_name, value ? value : "(not set)");
}
#include "../includes/minishell.h"

// 1. export (no arguments - should print all exported variables)
t_pipeline *test_export_no_args()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("export", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. export VAR=value (create new variable with value)
t_pipeline *test_export_new_var()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("NEW_VAR=hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. export EXISTING_VAR=new_value (modify existing variable)
t_pipeline *test_export_modify_existing()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("PATH=/new/path", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. export VAR (export existing variable without value assignment)
t_pipeline *test_export_existing_var()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("EXISTING_VAR", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. export NONEXISTENT_VAR (export non-existing variable without value)
t_pipeline *test_export_nonexistent_var()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("NONEXISTENT_VAR", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. export VAR="" (export variable with empty value)
t_pipeline *test_export_empty_value()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("EMPTY_VAR=", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. export VAR="value with spaces" (export with quoted value)
t_pipeline *test_export_quoted_value()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("QUOTED_VAR=hello world", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. export VAR1=value1 VAR2=value2 (multiple exports in one command)
t_pipeline *test_export_multiple_vars()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("VAR1=value1", TOKEN_ARGUMENT);
    tokens[2] = create_token("VAR2=value2", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. export 123INVALID=value (invalid variable name - starts with number)
t_pipeline *test_export_invalid_name_number()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("123INVALID=value", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 10. export INVALID-NAME=value (invalid variable name - contains hyphen)
t_pipeline *test_export_invalid_name_hyphen()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("INVALID-NAME=value", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 11. export INVALID@NAME=value (invalid variable name - special character)
t_pipeline *test_export_invalid_name_special()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("INVALID@NAME=value", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 12. export _VALID_NAME=value (valid variable name with underscore)
t_pipeline *test_export_valid_underscore()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("_VALID_NAME=underscore_value", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 13. export VALID123=value (valid variable name with numbers at end)
t_pipeline *test_export_valid_with_numbers()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("VALID123=valid_with_numbers", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 14. export VAR=value_with_equals=sign (value containing equals sign)
t_pipeline *test_export_value_with_equals()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("EQUALS_VAR=key=value", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 15. export = (just equals sign)
t_pipeline *test_export_just_equals()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("=", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 16. export =value (no variable name, just value)
t_pipeline *test_export_no_name()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("=somevalue", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 17. export "" (empty string)
t_pipeline *test_export_empty_string()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 18. export VAR1=value1 INVALID@VAR=bad VAR2=value2 (mix of valid/invalid)
t_pipeline *test_export_mixed_validity()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("VAR1=mixed_value1", TOKEN_ARGUMENT);
    tokens[2] = create_token("INVALID@VAR=bad_value", TOKEN_ARGUMENT);
    tokens[3] = create_token("VAR2=mixed_value2", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 19. export HOME=/new/home (override critical system variable)
t_pipeline *test_export_override_home()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("HOME=/new/home/directory", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 20. export PWD=/custom/pwd (override PWD)
t_pipeline *test_export_override_pwd()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("export", TOKEN_COMMAND);
    tokens[1] = create_token("PWD=/custom/pwd/path", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// Environment setup helper for export testing
void setup_export_test_environment(t_shell *shell)
{
    // Set up some existing variables for testing
    set_env_variable(&shell->environment, "EXISTING_VAR", "existing_value");
    set_env_variable(&shell->environment, "PATH", "/usr/bin:/bin");
    set_env_variable(&shell->environment, "HOME", "/Users/testuser");
    set_env_variable(&shell->environment, "PWD", "/current/directory");
}
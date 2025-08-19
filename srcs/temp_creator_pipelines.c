#include "../includes/minishell.h"

// ========== BASIC PIPELINES ==========

// 1. echo "hello" | cat (basic two-command pipeline)
t_pipeline *test_pipeline_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: echo "hello"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: cat
    t_token *tokens2[1];
    tokens2[0] = create_token("cat", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 2. ls | grep txt (filter pipeline)
t_pipeline *test_pipeline_filter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: ls
    t_token *tokens1[2];
    tokens1[0] = create_token("ls", TOKEN_COMMAND);
    tokens1[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 2);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: grep txt
    t_token *tokens2[2];
    tokens2[0] = create_token("grep", TOKEN_COMMAND);
    tokens2[1] = create_token("txt", TOKEN_ARGUMENT);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 3. cat file.txt | wc -l (count lines in file)
t_pipeline *test_pipeline_count_lines()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: cat file.txt
    t_token *tokens1[3];
    tokens1[0] = create_token("cat", TOKEN_COMMAND);
    tokens1[1] = create_token("file.txt", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: wc -l
    t_token *tokens2[2];
    tokens2[0] = create_token("wc", TOKEN_COMMAND);
    tokens2[1] = create_token("-l", TOKEN_ARGUMENT);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// ========== THREE-COMMAND PIPELINES ==========

// 4. ls | grep txt | wc -l (three-stage filter and count)
t_pipeline *test_pipeline_three_commands()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 3;
    pipeline->token_lists = malloc(3 * sizeof(t_token*));

    // First command: ls
    t_token *tokens1[2];
    tokens1[0] = create_token("ls", TOKEN_COMMAND);
    tokens1[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 2);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: grep txt
    t_token *tokens2[3];
    tokens2[0] = create_token("grep", TOKEN_COMMAND);
    tokens2[1] = create_token("txt", TOKEN_ARGUMENT);
    tokens2[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens2, 3);
    pipeline->token_lists[1] = tokens2[0];

    // Third command: wc -l
    t_token *tokens3[2];
    tokens3[0] = create_token("wc", TOKEN_COMMAND);
    tokens3[1] = create_token("-l", TOKEN_ARGUMENT);
    link_tokens(tokens3, 2);
    pipeline->token_lists[2] = tokens3[0];

    return pipeline;
}

// 5. echo "apple\nbanana\ncherry" | sort | head -n 2 (sort and limit output)
t_pipeline *test_pipeline_sort_limit()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 3;
    pipeline->token_lists = malloc(3 * sizeof(t_token*));

    // First command: echo "apple\nbanana\ncherry"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("apple\nbanana\ncherry", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: sort
    t_token *tokens2[2];
    tokens2[0] = create_token("sort", TOKEN_COMMAND);
    tokens2[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    // Third command: head -n 2
    t_token *tokens3[3];
    tokens3[0] = create_token("head", TOKEN_COMMAND);
    tokens3[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens3[2] = create_token("2", TOKEN_ARGUMENT);
    link_tokens(tokens3, 3);
    pipeline->token_lists[2] = tokens3[0];

    return pipeline;
}

// ========== LONG PIPELINES ==========

// 6. echo "data" | cat | cat | cat | cat (four pipe chain)
t_pipeline *test_pipeline_long_chain()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 5;
    pipeline->token_lists = malloc(5 * sizeof(t_token*));

    // First command: echo "data"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("data", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Commands 2-4: cat
    for (int i = 1; i < 4; i++) {
        t_token *tokens[2];
        tokens[0] = create_token("cat", TOKEN_COMMAND);
        tokens[1] = create_token("|", TOKEN_PIPE);
        link_tokens(tokens, 2);
        pipeline->token_lists[i] = tokens[0];
    }

    // Last command: cat (no pipe)
    t_token *tokens5[1];
    tokens5[0] = create_token("cat", TOKEN_COMMAND);
    link_tokens(tokens5, 1);
    pipeline->token_lists[4] = tokens5[0];

    return pipeline;
}

// ========== PIPELINES WITH BUILT-INS ==========

// 7. echo "test" | cat (builtin to external)
t_pipeline *test_pipeline_builtin_to_external()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: echo "test" (builtin)
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("test", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: cat (external)
    t_token *tokens2[1];
    tokens2[0] = create_token("cat", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 8. ls | env (external to builtin)
t_pipeline *test_pipeline_external_to_builtin()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: ls (external)
    t_token *tokens1[2];
    tokens1[0] = create_token("ls", TOKEN_COMMAND);
    tokens1[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 2);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: env (builtin)
    t_token *tokens2[1];
    tokens2[0] = create_token("env", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// ========== PIPELINES WITH REDIRECTIONS ==========

// 9. echo "hello" | cat > output.txt (pipeline with output redirection)
t_pipeline *test_pipeline_with_output_redirect()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: echo "hello"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: cat > output.txt
    t_token *tokens2[3];
    tokens2[0] = create_token("cat", TOKEN_COMMAND);
    tokens2[1] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens2[2] = create_token("output.txt", TOKEN_FILE);
    link_tokens(tokens2, 3);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 10. cat < input.txt | grep "pattern" (input redirection with pipeline)
t_pipeline *test_pipeline_with_input_redirect()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: cat < input.txt
    t_token *tokens1[4];
    tokens1[0] = create_token("cat", TOKEN_COMMAND);
    tokens1[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens1[2] = create_token("input.txt", TOKEN_FILE);
    tokens1[3] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 4);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: grep "pattern"
    t_token *tokens2[2];
    tokens2[0] = create_token("grep", TOKEN_COMMAND);
    tokens2[1] = create_token("pattern", TOKEN_ARGUMENT);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// ========== PIPELINES WITH HEREDOC ==========

// 11. cat << EOF | wc -l (heredoc with pipeline)
t_pipeline *test_pipeline_with_heredoc()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: cat << EOF
    t_token *tokens1[4];
    tokens1[0] = create_token("cat", TOKEN_COMMAND);
    tokens1[1] = create_token("<<", TOKEN_HEREDOC);
    tokens1[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens1[3] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 4);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: wc -l
    t_token *tokens2[2];
    tokens2[0] = create_token("wc", TOKEN_COMMAND);
    tokens2[1] = create_token("-l", TOKEN_ARGUMENT);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// ========== COMPLEX COMBINATIONS ==========

// 12. cat < input.txt | sort | grep "pattern" > filtered.txt (full combination)
t_pipeline *test_pipeline_complex_combination()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 3;
    pipeline->token_lists = malloc(3 * sizeof(t_token*));

    // First command: cat < input.txt
    t_token *tokens1[4];
    tokens1[0] = create_token("cat", TOKEN_COMMAND);
    tokens1[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens1[2] = create_token("input.txt", TOKEN_FILE);
    tokens1[3] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 4);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: sort
    t_token *tokens2[2];
    tokens2[0] = create_token("sort", TOKEN_COMMAND);
    tokens2[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    // Third command: grep "pattern" > filtered.txt
    t_token *tokens3[4];
    tokens3[0] = create_token("grep", TOKEN_COMMAND);
    tokens3[1] = create_token("pattern", TOKEN_ARGUMENT);
    tokens3[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens3[3] = create_token("filtered.txt", TOKEN_FILE);
    link_tokens(tokens3, 4);
    pipeline->token_lists[2] = tokens3[0];

    return pipeline;
}

// ========== ERROR CASES ==========

// 13. nonexistent_cmd | cat (error in first command)
t_pipeline *test_pipeline_error_first_command()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: nonexistent_cmd
    t_token *tokens1[2];
    tokens1[0] = create_token("nonexistent_cmd", TOKEN_COMMAND);
    tokens1[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 2);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: cat
    t_token *tokens2[1];
    tokens2[0] = create_token("cat", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 14. echo "test" | nonexistent_cmd (error in second command)
t_pipeline *test_pipeline_error_second_command()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: echo "test"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("test", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: nonexistent_cmd
    t_token *tokens2[1];
    tokens2[0] = create_token("nonexistent_cmd", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}

// 15. echo "test" | cat | nonexistent_cmd (error in last command)
t_pipeline *test_pipeline_error_last_command()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 3;
    pipeline->token_lists = malloc(3 * sizeof(t_token*));

    // First command: echo "test"
    t_token *tokens1[3];
    tokens1[0] = create_token("echo", TOKEN_COMMAND);
    tokens1[1] = create_token("test", TOKEN_ARGUMENT);
    tokens1[2] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens1, 3);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: cat
    t_token *tokens2[2];
    tokens2[0] = create_token("cat", TOKEN_COMMAND);
    tokens2[1] = create_token("|", TOKEN_PIPE);
    link_tokens(tokens2, 2);
    pipeline->token_lists[1] = tokens2[0];

    // Third command: nonexistent_cmd
    t_token *tokens3[1];
    tokens3[0] = create_token("nonexistent_cmd", TOKEN_COMMAND);
    link_tokens(tokens3, 1);
    pipeline->token_lists[2] = tokens3[0];

    return pipeline;
}
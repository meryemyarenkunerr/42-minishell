#include "../includes/minishell.h"

// ========== OUTPUT REDIRECTION (>) ==========

// 1. echo "hello" > output.txt (basic output redirection)
t_pipeline *test_output_redirection_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("output.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. ls > files.txt (command output to file)
t_pipeline *test_output_redirection_ls()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("ls", TOKEN_COMMAND);
    tokens[1] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[2] = create_token("files.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. echo "text" > /tmp/test.txt (absolute path)
t_pipeline *test_output_redirection_absolute_path()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("text", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("/tmp/test.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. echo "overwrite" > existing.txt (overwrite existing file)
t_pipeline *test_output_redirection_overwrite()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("overwrite", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("existing.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== APPEND REDIRECTION (>>) ==========

// 5. echo "append" >> output.txt (basic append)
t_pipeline *test_append_redirection_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("append", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("output.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. ls -la >> log.txt (append command output)
t_pipeline *test_append_redirection_ls()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("ls", TOKEN_COMMAND);
    tokens[1] = create_token("-la", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("log.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. echo "new line" >> /tmp/append.txt (append with absolute path)
t_pipeline *test_append_redirection_absolute()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("new line", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("/tmp/append.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== INPUT REDIRECTION (<) ==========

// 8. cat < input.txt (basic input redirection)
t_pipeline *test_input_redirection_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("input.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. wc -l < data.txt (input redirection with flags)
t_pipeline *test_input_redirection_wc()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("wc", TOKEN_COMMAND);
    tokens[1] = create_token("-l", TOKEN_ARGUMENT);
    tokens[2] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[3] = create_token("data.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 10. sort < /tmp/unsorted.txt (input redirection absolute path)
t_pipeline *test_input_redirection_absolute()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("/tmp/unsorted.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 11. grep "pattern" < search.txt (input redirection with grep)
t_pipeline *test_input_redirection_grep()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("grep", TOKEN_COMMAND);
    tokens[1] = create_token("pattern", TOKEN_ARGUMENT);
    tokens[2] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[3] = create_token("search.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== COMBINED REDIRECTIONS ==========

// 12. cat < input.txt > output.txt (input and output redirection)
t_pipeline *test_combined_input_output()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("input.txt", TOKEN_FILE);
    tokens[3] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[4] = create_token("output.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 13. sort < data.txt >> sorted.txt (input redirection with append)
t_pipeline *test_combined_input_append()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("data.txt", TOKEN_FILE);
    tokens[3] = create_token(">>", TOKEN_APPEND);
    tokens[4] = create_token("sorted.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 14. grep "pattern" < input.txt > matches.txt (grep with both redirections)
t_pipeline *test_combined_grep_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("grep", TOKEN_COMMAND);
    tokens[1] = create_token("pattern", TOKEN_ARGUMENT);
    tokens[2] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[3] = create_token("input.txt", TOKEN_FILE);
    tokens[4] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[5] = create_token("matches.txt", TOKEN_FILE);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== MULTIPLE OUTPUT REDIRECTIONS ==========

// 15. echo "test" > file1.txt > file2.txt (multiple output - last one wins)
t_pipeline *test_multiple_output_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("test", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("file1.txt", TOKEN_FILE);
    tokens[4] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[5] = create_token("file2.txt", TOKEN_FILE);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 16. echo "test" >> file1.txt >> file2.txt (multiple append)
t_pipeline *test_multiple_append_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("meryem", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("file1.txt", TOKEN_FILE);
    tokens[4] = create_token(">>", TOKEN_APPEND);
    tokens[5] = create_token("file2.txt", TOKEN_FILE);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 17. cat < file1.txt < file2.txt (multiple input - last one wins)
t_pipeline *test_multiple_input_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("file1.txt", TOKEN_FILE);
    tokens[3] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[4] = create_token("file2.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== REDIRECTIONS WITH HEREDOC ==========

// 18. cat << EOF > output.txt (heredoc with output redirection)
t_pipeline *test_heredoc_with_output()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[3] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[4] = create_token("output.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 19. sort << EOF >> sorted.txt (heredoc with append)
t_pipeline *test_heredoc_with_append()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[3] = create_token(">>", TOKEN_APPEND);
    tokens[4] = create_token("sorted.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== ERROR CASES ==========

// 20. echo "test" > /nonexistent/path/file.txt (permission denied)
t_pipeline *test_output_permission_denied()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("test", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("/nonexistent/path/file.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 21. cat < nonexistent.txt (input file not found)
t_pipeline *test_input_file_not_found()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("nonexistent.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 22. cat > /dev/null (output to special file)
t_pipeline *test_output_to_dev_null()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[2] = create_token("/dev/null", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// ========== COMPLEX COMBINATIONS ==========

// 23. cat < input.txt > output1.txt > output2.txt (multiple mixed redirections)
t_pipeline *test_complex_multiple_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[7];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[2] = create_token("input.txt", TOKEN_FILE);
    tokens[3] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[4] = create_token("output1.txt", TOKEN_FILE);
    tokens[5] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[6] = create_token("output2.txt", TOKEN_FILE);

    link_tokens(tokens, 7);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 24. sort -r < data.txt >> results.txt (flags with redirections)
t_pipeline *test_flags_with_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("-r", TOKEN_ARGUMENT);
    tokens[2] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[3] = create_token("data.txt", TOKEN_FILE);
    tokens[4] = create_token(">>", TOKEN_APPEND);
    tokens[5] = create_token("results.txt", TOKEN_FILE);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 25. head -n 5 < large.txt > small.txt (complex command with redirections)
t_pipeline *test_complex_command_redirections()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[7];
    tokens[0] = create_token("head", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("5", TOKEN_ARGUMENT);
    tokens[3] = create_token("<", TOKEN_REDIRECT_IN);
    tokens[4] = create_token("large.txt", TOKEN_FILE);
    tokens[5] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[6] = create_token("small.txt", TOKEN_FILE);

    link_tokens(tokens, 7);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}
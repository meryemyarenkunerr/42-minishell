#include "../includes/minishell.h"

// 1. cat << EOF (basic heredoc)
t_pipeline *test_heredoc_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. cat << DELIMITER (custom delimiter)
t_pipeline *test_heredoc_custom_delimiter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("DELIMITER", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. cat << END123 (delimiter with numbers)
t_pipeline *test_heredoc_delimiter_with_numbers()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("END123", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. cat << _UNDERSCORE_ (delimiter with underscores)
t_pipeline *test_heredoc_delimiter_underscore()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("_UNDERSCORE_", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. grep "pattern" << EOF (heredoc with grep)
t_pipeline *test_heredoc_with_grep()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("grep", TOKEN_COMMAND);
    tokens[1] = create_token("pattern", TOKEN_ARGUMENT);
    tokens[2] = create_token("<<", TOKEN_HEREDOC);
    tokens[3] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. wc -l << EOF (heredoc with wc)
t_pipeline *test_heredoc_with_wc()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("wc", TOKEN_COMMAND);
    tokens[1] = create_token("-l", TOKEN_ARGUMENT);
    tokens[2] = create_token("<<", TOKEN_HEREDOC);
    tokens[3] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. cat << EOF file.txt (heredoc with additional file argument)
t_pipeline *test_heredoc_with_file()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[3] = create_token("file.txt", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. cat << "EOF" (quoted delimiter)
t_pipeline *test_heredoc_quoted_delimiter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("\"EOF\"", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. cat << 'EOF' (single quoted delimiter)
t_pipeline *test_heredoc_single_quoted_delimiter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("'EOF'", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 10. cat << A (single character delimiter)
t_pipeline *test_heredoc_single_char_delimiter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("A", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 11. cat << VERY_LONG_DELIMITER_NAME (long delimiter)
t_pipeline *test_heredoc_long_delimiter()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("VERY_LONG_DELIMITER_NAME", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 12. cat -n << EOF (command with flags and heredoc)
t_pipeline *test_heredoc_with_command_flags()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("<<", TOKEN_HEREDOC);
    tokens[3] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 13. sort << EOF (heredoc with sort command)
t_pipeline *test_heredoc_with_sort()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 14. head -n 3 << EOF (heredoc with head command)
t_pipeline *test_heredoc_with_head()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("head", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("3", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 15. tr 'a' 'b' << EOF (heredoc with tr command)
t_pipeline *test_heredoc_with_tr()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("tr", TOKEN_COMMAND);
    tokens[1] = create_token("a", TOKEN_ARGUMENT);
    tokens[2] = create_token("b", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 16. cat << EOF << END (multiple heredocs - last one should be used)
t_pipeline *test_multiple_heredocs_cat()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("END", TOKEN_ARGUMENT);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 17. grep "pattern" << FIRST << SECOND (multiple heredocs with grep)
t_pipeline *test_multiple_heredocs_grep()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("grep", TOKEN_COMMAND);
    tokens[1] = create_token("pattern", TOKEN_ARGUMENT);
    tokens[2] = create_token("<<", TOKEN_HEREDOC);
    tokens[3] = create_token("FIRST", TOKEN_ARGUMENT);
    tokens[4] = create_token("<<", TOKEN_HEREDOC);
    tokens[5] = create_token("SECOND", TOKEN_ARGUMENT);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 18. wc -l << DATA1 << DATA2 << DATA3 (three heredocs)
t_pipeline *test_triple_heredocs()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[8];
    tokens[0] = create_token("wc", TOKEN_COMMAND);
    tokens[1] = create_token("-l", TOKEN_ARGUMENT);
    tokens[2] = create_token("<<", TOKEN_HEREDOC);
    tokens[3] = create_token("DATA1", TOKEN_ARGUMENT);
    tokens[4] = create_token("<<", TOKEN_HEREDOC);
    tokens[5] = create_token("DATA2", TOKEN_ARGUMENT);
    tokens[6] = create_token("<<", TOKEN_HEREDOC);
    tokens[7] = create_token("DATA3", TOKEN_ARGUMENT);

    link_tokens(tokens, 8);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 19. sort << UNSORTED << SORTED (multiple heredocs with sort)
t_pipeline *test_multiple_heredocs_sort()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("sort", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("UNSORTED", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("SORTED", TOKEN_ARGUMENT);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 20. cat << A << B file.txt << C (heredocs mixed with file argument)
t_pipeline *test_heredocs_with_file_mixed()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[8];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("A", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("B", TOKEN_ARGUMENT);
    tokens[5] = create_token("file.txt", TOKEN_ARGUMENT);
    tokens[6] = create_token("<<", TOKEN_HEREDOC);
    tokens[7] = create_token("C", TOKEN_ARGUMENT);

    link_tokens(tokens, 8);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 21. head -n 2 << FIRST << SECOND << THIRD (multiple heredocs with head)
t_pipeline *test_multiple_heredocs_head()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[9];
    tokens[0] = create_token("head", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("2", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("FIRST", TOKEN_ARGUMENT);
    tokens[5] = create_token("<<", TOKEN_HEREDOC);
    tokens[6] = create_token("SECOND", TOKEN_ARGUMENT);
    tokens[7] = create_token("<<", TOKEN_HEREDOC);
    tokens[8] = create_token("THIRD", TOKEN_ARGUMENT);

    link_tokens(tokens, 9);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 22. tr 'a' 'b' << INPUT1 << INPUT2 (multiple heredocs with tr)
t_pipeline *test_multiple_heredocs_tr()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[7];
    tokens[0] = create_token("tr", TOKEN_COMMAND);
    tokens[1] = create_token("a", TOKEN_ARGUMENT);
    tokens[2] = create_token("b", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("INPUT1", TOKEN_ARGUMENT);
    tokens[5] = create_token("<<", TOKEN_HEREDOC);
    tokens[6] = create_token("INPUT2", TOKEN_ARGUMENT);

    link_tokens(tokens, 7);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 23. cat << EOF << EOF << EOF (same delimiter multiple times)
t_pipeline *test_same_delimiter_multiple()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[7];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("EOF", TOKEN_ARGUMENT);
    tokens[5] = create_token("<<", TOKEN_HEREDOC);
    tokens[6] = create_token("EOF", TOKEN_ARGUMENT);

    link_tokens(tokens, 7);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 24. uniq << DATA << MOREDATA (multiple heredocs with uniq)
t_pipeline *test_multiple_heredocs_uniq()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("uniq", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("DATA", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("MOREDATA", TOKEN_ARGUMENT);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 25. rev << TEXT1 << TEXT2 << TEXT3 << TEXT4 (four heredocs with rev)
t_pipeline *test_quadruple_heredocs()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[9];
    tokens[0] = create_token("rev", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("TEXT1", TOKEN_ARGUMENT);
    tokens[3] = create_token("<<", TOKEN_HEREDOC);
    tokens[4] = create_token("TEXT2", TOKEN_ARGUMENT);
    tokens[5] = create_token("<<", TOKEN_HEREDOC);
    tokens[6] = create_token("TEXT3", TOKEN_ARGUMENT);
    tokens[7] = create_token("<<", TOKEN_HEREDOC);
    tokens[8] = create_token("TEXT4", TOKEN_ARGUMENT);

    link_tokens(tokens, 9);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}
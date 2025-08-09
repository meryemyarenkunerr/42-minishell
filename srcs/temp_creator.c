#include "../includes/minishell.h"

// Yardımcı: string copy
static char *strdup_simple_temp(const char *s)
{
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    strcpy(copy, s);
    return copy;
}

// Sabit uzunluklu argüman dizisi oluşturur, NULL ile sonlandırır
char **create_arguments_temp_fixed(int count, const char **args)
{
    char **array = malloc(sizeof(char*) * (count + 1));
    if (!array)
        return NULL;
    for (int i = 0; i < count; i++)
        array[i] = strdup_simple_temp(args[i]);
    array[count] = NULL;
    return array;
}

// Sabit uzunluklu heredoc delimiters dizisi oluşturur, NULL ile sonlandırır
char **create_heredoc_delimiters_temp_fixed(int count, const char **delims)
{
    char **array = malloc(sizeof(char*) * (count + 1));
    if (!array)
        return NULL;
    for (int i = 0; i < count; i++)
        array[i] = strdup_simple_temp(delims[i]);
    array[count] = NULL;
    return array;
}

t_command *create_command_temp(const char *cmd, char **arguments,
                              char *input_file, char *output_file,
                              int append_mode, char **heredoc_delim)
{
    t_command *command = malloc(sizeof(t_command));
    if (!command)
        return NULL;
    command->cmd = strdup_simple_temp(cmd);
    command->arguments = arguments; // dışarıdan malloc'lu array
    command->input_file = input_file ? strdup_simple_temp(input_file) : NULL;
    command->output_file = output_file ? strdup_simple_temp(output_file) : NULL;
    command->append_mode = append_mode;
    command->heredoc_delimeter = heredoc_delim; // NULL veya malloc'lu array
    command->next = NULL;
    command->pipeline = NULL;
    return command;
}

t_command *build_commands_for_example_temp(void)
{
    // 1. komut: cat << EOF
    const char *cat_args[] = {"cat"};
    char **cat_args_arr = create_arguments_temp_fixed(1, cat_args);

    const char *heredocs[] = {"EOF"};
    char **cat_heredoc_arr = create_heredoc_delimiters_temp_fixed(1, heredocs);

    t_command *cmd1 = create_command_temp("cat", cat_args_arr, NULL, NULL, 0, cat_heredoc_arr);

    // 2. komut: wc -l
    const char *wc_args[] = {"wc", "-l"};
    char **wc_args_arr = create_arguments_temp_fixed(2, wc_args);
    t_command *cmd2 = create_command_temp("wc", wc_args_arr, NULL, NULL, 0, NULL);

    cmd1->next = cmd2;

    // Pipeline pointer ayarla (opsiyonel)
    cmd1->pipeline = NULL;
    cmd2->pipeline = NULL;

    return cmd1; // komut listesinin başı
}

void free_arguments_temp(char **args)
{
    if (!args) return;
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

void free_heredoc_delimiters_temp(char **heredocs)
{
    if (!heredocs) return;
    for (int i = 0; heredocs[i]; i++)
        free(heredocs[i]);
    free(heredocs);
}

void free_command_temp(t_command *cmd)
{
    if (!cmd)
        return;
    free(cmd->cmd);
    free_arguments_temp(cmd->arguments);
    free(cmd->input_file);
    free(cmd->output_file);
    free_heredoc_delimiters_temp(cmd->heredoc_delimeter);
    free_command_temp(cmd->next);
    free(cmd);
}
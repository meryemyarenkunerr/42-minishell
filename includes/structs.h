#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>

/* Token Types */
typedef enum e_token_types
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_FILE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_types;

/* Token Structure */
typedef struct s_token
{
	char			*content;
	t_token_types	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/* Command Structure */
typedef struct s_command
{
	char				*cmd;					// yeni eklendi, execve() için gerekli
	char				**arguments;
	char				*input_file;
	char				*output_file;
	char				**heredoc_delimeter;	// birden fazla delimeter olabilir
	int					append_mode;
	struct s_command	*next;
	struct s_pipeline	*pipeline;
}	t_command;

/* Pipeline Structure - Token Lists seperated by pipes */
typedef struct s_pipeline
{
	t_token	**token_lists;
	int		*heredoc_count;
	int		count;
}	t_pipeline;

/* Environment Structure */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Shell Structure */
typedef struct s_shell
{
	t_env			*environment;
	struct termios	term_backup;
	int				exit_status;
	char			*prompt;
	int				cmd_has_been_executed;
	t_command		*commands;
	char			*home_dir;
	char			*current_dir;
}	t_shell;

#endif
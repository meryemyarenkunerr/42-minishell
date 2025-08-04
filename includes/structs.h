#ifndef STRUCTS_H
# define STRUCTS_H

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
	char				**args;
	char				*input;
	char				*out;
	int					append_mode;
	struct s_command	*next;
}	t_command;

/* Pipeline Structure */
typedef struct s_redirect
{
	t_token	**token_lists;
	int		count;
}	t_redirect;

/* Environment Structure */
typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}	t_env;

/* Shell Structure */
typedef struct s_shell
{
	// environment variables
	char		**env;
	t_env		*env_head;
	char		**cmd_paths;
	char		*user_name;					// ne kadar gerekli olduğuna bakacaazzz

	// state flags
	int			exit_code;
	int			cmd_has_been_executed;		// TRUE or FALSE
	int			print;						// TRUE or FALSE
	int			color_codes;				// if color usage exists

	// command and prompt info
	char		*terminal_prompt;
	t_command	*commands;					// command list

	// heredoc
	char		*heredoc_temp;
	int			*expand_heredoc;

	// input/output
	int			std_fds[2];

	// execution
	int			exec_on_pipe;				// ne kadar gerekli olduğuna bakacaazzz (parser'dan gelen veriye bağlı)
	int			execute;					// ne zaman çalışacak buna karar veriyor
}	t_shell;

#endif
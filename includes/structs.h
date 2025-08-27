/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:02:09 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 08:40:13 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_types
{
	TOKEN_NONE,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_FILE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_EOF_QUOTE,
	TOKEN_SKIP,
}	t_token_types;

typedef struct s_token
{
	char			*content;
	t_token_types	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*cmd;
	char				**arguments;
	char				**input_files;
	char				**output_files;
	char				**ordered_all_files;
	int					input_count;
	int					output_count;
	char				**heredoc_delimiter;
	int					heredoc_count;
	int					quote_flag;
	int					*append_modes;
	int					file_handler;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline
{
	t_token	**token_lists;
	int		count;
}	t_pipeline;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env			*environment;
	int				exit_status;
	int				exit;
	t_command		*commands;
	t_pipeline		*pipeline;
}	t_shell;

#endif

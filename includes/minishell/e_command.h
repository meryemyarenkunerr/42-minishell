/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 12:22:50 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMAND_H
#define MINISHELL_COMMAND_H

#include "../structs.h"

typedef struct s_token t_token;
typedef struct s_command t_command;
typedef struct s_shell t_shell;

/* EXECUTER/COMMAND */
/* command_builder.c */
int				builds_commands_from_pipeline(t_shell *shell);

/* command_creation.c */
int				is_valid_argument_token(t_token *token, const char *cmd_name);
int				fill_command_arguments(t_command *cmd, t_token *token_list,
					int arg_count);
int				extract_command_and_args(t_command *cmd, t_token *token_list);
void			extract_redirections_and_heredocs(t_command *cmd,
					t_token *token_list);
t_command		*create_command_from_tokens(t_token *token_list);

/* expander.c */
char			*expand_variable(char *line, t_shell *shell);

/* heredoc_management.c */
void			add_heredoc_delimiter_with_quote(t_command *cmd,
					const char *delimiter, int is_quoted);

/* token_analysis.c */
int				is_redirection_file(t_token *token);
int				is_heredoc_delimeter(t_token *token);
char			*find_command_name(t_token *token_list);
int				argument_counter(t_token *token_list);

/* utils.c */
t_command		*init_command(void);
t_token			*handle_redirection(t_command *cmd, t_token *current);
void			add_input_file(t_command *cmd, const char *filename);
t_command		*create_empty_command_with_redirections(t_token *token_list);

/* utils2.c */
void			add_output_file(t_command *cmd, const char *filename,
					int append_mode);
void			add_to_ordered_files(t_command *cmd, const char *filename);

#endif // MINISHELL_COMMAND_H

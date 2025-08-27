/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:46:16 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_COMMAND_H
# define E_COMMAND_H

# include "../structs.h"

int			builds_commands_from_pipeline(t_shell *shell);
t_command	*create_command_from_tokens(t_token *token_list);
t_command	*create_empty_command_with_redirections(t_token *token_list);
int			fill_command_arguments(t_command *cmd, t_token *token_list,
				int arg_count);
char		*find_command_name(t_token *token_list);
char		*expand_variable(char *line, t_shell *shell);
void		add_input_file(t_command *cmd, const char *filename);
void		add_output_file(t_command *cmd, const char *filename,
				int append_mode);
void		add_to_ordered_files(t_command *cmd, const char *filename);
void		add_heredoc_delimiter_with_quote(t_command *cmd,
				const char *delimiter, int is_quoted);
int			allocate_new_arrays(t_command *cmd, char ***new_files,
				int **new_modes);
int			is_valid_argument_token(t_token *token, const char *cmd_name);
t_command	*init_command(void);

#endif

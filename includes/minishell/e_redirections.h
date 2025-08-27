/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirections.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 05:37:44 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_REDIRECTIONS_H
# define E_REDIRECTIONS_H

# include "../structs.h"

int		setup_file_descriptors(t_shell *shell);
int		setup_single_input_file(t_shell *shell, t_command *cmd, char *filename);
int		setup_single_output_file(t_shell *shell, t_command *cmd, char *filename,
			int append_mode);
int		is_output_file(t_command *cmd, char *filename);
int		is_input_file(t_command *cmd, char *filename);

#endif

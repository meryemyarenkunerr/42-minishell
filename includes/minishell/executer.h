/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:30:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:30:02 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../structs.h"

void	executer(t_shell *shell);
void	execute_single_command(t_shell *shell, t_command *cmd);
int		ft_strcmp(const char *s1, const char *s2);

#endif

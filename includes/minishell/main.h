/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:30:05 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:30:07 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../structs.h"
# include "../defines.h"

int		add_key_value_pair(t_env **env, char *env_pair);
void	init_shell(t_shell *shell, char **env);
void	process_command(t_shell *shell, char *command);
char	*build_prompt(void);
void	shell_loop(t_shell *shell);

#endif

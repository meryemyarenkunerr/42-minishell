/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:22:50 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:44:09 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_BUILTINS_H
# define E_BUILTINS_H

# include "../structs.h"

void	execute_builtin_pwd(t_shell *shell, t_command *cmd);
void	execute_builtin_env(t_shell *shell, t_command *cmd);
void	execute_builtin_cd(t_shell *shell, t_command *cmd);
void	execute_builtin_echo(t_shell *shell, t_command *cmd);
void	execute_builtin_exit(t_shell *shell, t_command *cmd);
void	check_and_print_export(int flag, t_env **array, int idx);
void	sort_env_array(t_env **array, int size);
void	copy_env_to_array(t_env *env, t_env **array);
int		count_env_keys(t_env *env);
int		is_valid_identifier_export(const char *str);
void	execute_builtin_export(t_shell *shell, t_command *cmd);
void	execute_builtin_unset(t_shell *shell, t_command *cmd);
void	execute_builtin(t_shell *shell, t_command *cmd);
void	call_builtin_function(t_shell *shell, t_command *cmd);
int		is_builtin_command(const char *cmd);
void	update_pwd_env(t_shell *shell, char *old_pwd);
char	*get_env_value(t_env *env, const char *key);
void	set_env_variable(t_env **env, const char *key, const char *val);
void	remove_env_variable(t_env **env, const char *key);
int		cmd_counter_except_first(t_command *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 15:57:58 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*build_full_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;
	int		total_len;

	if (!dir || !cmd)
		return (NULL);
	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	total_len = dir_len + cmd_len + 2;
	full_path = malloc(total_len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, total_len);
	if (dir[dir_len - 1] != '/')
		ft_strlcat(full_path, "/", total_len);
	ft_strlcat(full_path, cmd, total_len);
	return (full_path);
}

char	*check_path_directories(char **path_dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		full_path = build_full_path(path_dirs[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	return (NULL);
}

char	*search_in_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	**path_dirs;
	char	*res;

	path_env = get_env_value(shell->environment, "PATH");
	if (!path_env)
		return (current_directory(shell, cmd));
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (current_directory(shell, cmd));
	res = check_path_directories(path_dirs, cmd);
	free_string_array(path_dirs);
	return (res);
}

char	*check_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*find_executable_path(t_shell *shell, char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (check_direct_path(cmd));
	if (cmd[0] == '\0')
		return (ft_strdup("/bin/usr/true"));
	return (search_in_path(shell, cmd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_remain(char *read_line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (read_line[i] != '\0' && read_line[i] != '\n')
		i++;
	if (!read_line[i])
	{
		return (free(read_line), NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen(read_line) - i));
	if (!temp)
		return (free(temp), NULL);
	i++;
	j = 0;
	while (read_line[i + j])
	{
		temp[j] = read_line[i + j];
		j++;
	}
	temp[j] = '\0';
	free(read_line);
	return (temp);
}

char	*extract_new_line(char *read_line)
{
	char	*temp;
	int		i;

	i = 0;
	if (!read_line[i])
		return (0);
	while (read_line[i] && read_line[i] != '\n')
		i++;
	temp = (char *)malloc((sizeof(char) * i) + 2);
	if (!temp)
		return (NULL);
	i = 0;
	while (read_line[i] && read_line[i] != '\n')
	{
		temp[i] = read_line[i];
		i++;
	}
	if (read_line[i] == '\n')
	{
		temp[i] = '\n';
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*read_from_file(int fd, char *read_line)
{
	char	*buffer;
	int		count;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	count = 1;
	while (!ft_strchr(read_line, '\n') && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free(read_line);
			return (0);
		}
		buffer[count] = '\0';
		read_line = ft_strjoin(read_line, buffer);
	}
	free(buffer);
	return (read_line);
}

char	*get_next_line(int fd)
{
	static char	*read_line;
	char		*new_line;

	new_line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	read_line = read_from_file(fd, read_line);
	if (!read_line)
		return (NULL);
	new_line = extract_new_line(read_line);
	read_line = get_remain(read_line);
	return (new_line);
}

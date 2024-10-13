/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafaisal <mafaisal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:05:07 by mafaisal          #+#    #+#             */
/*   Updated: 2023/12/04 15:06:07 by mafaisal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_to_line(char *line, int fd)
{
	char	*buf;
	ssize_t	status;
	char	*temp;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		status = read(fd, buf, BUFFER_SIZE);
		if (status <= 0)
		{
			if (status < 0 && line)
				return (free(line), free(buf), NULL);
			return (free(buf), line);
		}
		buf[status] = '\0';
		temp = line;
		line = ft_strjoin(line, buf);
		if (temp)
			free(temp);
		if (!line)
			return (free(buf), NULL);
	}
	return (free(buf), line);
}

char	*exact_line(char *line)
{
	char	*next_line;
	int		nl_len;

	nl_len = ft_strlen(line, '\n');
	next_line = malloc (nl_len + 1);
	if (!next_line)
		return (NULL);
	ft_copy(next_line, line, nl_len + 1);
	return (next_line);
}

char	*remaining_of_line(char *line)
{
	char		*remaining;
	int			remaining_len;

	remaining_len = ft_strlen(line, '\0') - (ft_strlen(line, '\n'));
	if (remaining_len == 0)
		return (free(line), NULL);
	remaining = malloc (remaining_len + 1);
	if (!remaining)
		return (NULL);
	ft_copy(remaining, line + ft_strlen(line, '\n'), remaining_len + 1);
	free(line);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*line[10240];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	line[fd] = read_to_line(line[fd], fd);
	if (!line[fd])
		return (NULL);
	next_line = exact_line(line[fd]);
	line[fd] = remaining_of_line(line[fd]);
	return (next_line);
}

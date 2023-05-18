/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:16:33 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 10:20:27 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*generate_buffer(int fd, char *buffer)
{
	char	*line;
	char	*join;

	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		return (buffer);
	}
	if (buffer)
	{
		join = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		return (generate_buffer(fd, join));
	}
	else
		return (generate_buffer(fd, line));
}

char	**get_buffer(int fd)
{
	char	*raw;
	char	**buffer;

	raw = generate_buffer(fd, NULL);
	buffer = ft_split(raw, '\n');
	free(raw);
	return (buffer);
}

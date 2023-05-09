/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/09 17:07:36 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "cub3d.h"

static char *generate_buffer(int fd, char *buffer, size_t *rows, size_t *cols)
{
	char	*line;
	char	*join;

	line = get_next_line(fd);
	if (!line)
		return (buffer);
	if (*rows == 0)
		*rows = ft_strlen(line) - 1;
	*cols += 1;
	if (buffer)
	{
		join = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		return (generate_buffer(fd, join, rows, cols));
	}
	else
	{
		return (generate_buffer(fd, line, rows, cols));
	}
}

t_game	generate_game(int fd)
{
	size_t	rows;
	size_t	cols;
	char	*raw;
	char	**buffer;

	rows = 0;
	cols = 0;
	raw = generate_buffer(fd, NULL, &rows, &cols);
	buffer = ft_split(raw, '\n');
	free(raw);
	return (t_game){.buffer = buffer, .rows = rows, .cols = cols};
}

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->cols)
	{
		free(game->buffer[i]);
		i += 1;
	}
	free(game->buffer);
}

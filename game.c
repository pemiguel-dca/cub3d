/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/15 14:54:01 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*generate_identifiers(int fd, char *buffer)
{
	char			*line;
	char			*join;
	static size_t	cols_ide = 0;

	if (cols_ide == 6)
		return (buffer);
	line = get_next_line(fd);
	while (line && ft_strcmp(line, "\n") == 0)
	{
		free(line);
		line = get_next_line(fd);
	}
	cols_ide += 1;
	if (buffer)
	{
		join = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		return (generate_identifiers(fd, join));
	}
	else
		return (generate_identifiers(fd, line));
}

static char	*generate_buffer(int fd, char *buffer, size_t *cols)
{
	char	*line;
	char	*join;

	line = get_next_line(fd);
	if (*cols == 0)
	{
		while (line && ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	if (!line || ft_strcmp(line, "\n") == 0)
	{
		free(line);
		return (buffer);
	}
	*cols += 1;
	if (buffer)
	{
		join = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		return (generate_buffer(fd, join, cols));
	}
	else
		return (generate_buffer(fd, line, cols));
}

t_game	generate_game(int fd)
{
	size_t	cols;
	char	*raw;
	char	*raw_identifiers;
	char	**buffer;
	char	**identifiers;

	cols = 0;
	raw_identifiers = generate_identifiers(fd, NULL);
	raw = generate_buffer(fd, NULL, &cols);
	buffer = ft_split(raw, '\n');
	identifiers = ft_split(raw_identifiers, '\n');
	free(raw);
	free(raw_identifiers);
	return ((t_game){.buffer = buffer, .cols = cols,
		.identifiers = identifiers, .rc = init_rc(buffer)});
}

t_vector	player_pos(const char **buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i][j])
		{
			if (is_cardinal_direction(buffer[i][j]))
				break ;
			j += 1;
		}
		i += 1;
	}
	return ((t_vector){.x = j, .y = i});
}

void	free_game(t_game *game)
{
	if (game->buffer)
		free_2Darrays(game->buffer);
	if (game->identifiers)
		free_2Darrays(game->identifiers);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_image(game->mlx, game->img_ptr);
		free(game->mlx);
	}
	if (game->rc)
		free(game->rc);
}

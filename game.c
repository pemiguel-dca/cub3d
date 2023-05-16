/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/16 20:16:11 by pnobre-m         ###   ########.fr       */
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

t_game	generate_game(char **buffer)
{
	char		**settings;
	size_t		i;

	settings = malloc(sizeof(char *) * N_SETTINGS);
	i = 0;
	while (i < N_SETTINGS)
	{
		settings[i] = *buffer;
		i += 1;
		buffer += 1;
	}
	return ((t_game){.map = buffer,
		.settings = settings, .rc = NULL});
}

void	free_game(t_game *game)
{
	size_t	i;

	i = 0;
	if (game->map)
		free_2Darrays(game->map);
	if (game->settings)
		free_2Darrays(game->settings);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
	}
	if (game->rc)
		free(game->rc);
}

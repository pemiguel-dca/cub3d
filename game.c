/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/17 17:38:47 by pemiguel         ###   ########.fr       */
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
	/*TODO: tens um leak aqui quando o map tem linhas vazias
	Exemplo:
	NO ./path_to_the_north_texture
	WE ./path_to_the_west_texture
	F 220,30,0
	SO ./path_to_the_south_texture
	EA ./path_to_the_east_texture


	*/
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
		.settings = settings});
}

void	free_game(t_game *game)
{
	if (game->map)
		free_2Darrays(game->map);
	if (game->settings)
		free_2Darrays(game->settings);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
	}
}

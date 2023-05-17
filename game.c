/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/17 20:13:26 by pnobre-m         ###   ########.fr       */
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

	n tem???
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
	int w;
	int h;
	t_game	game;
	size_t	sprites_i;
	size_t	colors_i;

	w = WIDTH;
	h = HEIGHT;
	sprites_i = 0;
	colors_i = 0;
	while (sprites_i + colors_i < N_SETTINGS)
	{
		char **split = ft_split(*buffer, ' ');
		if (!split[2])
		{
			void	*sprite = mlx_xpm_file_to_image(game.mlx, split[1], &w, &h);
			if (ft_strcmp(split[0], "NO"))
				game.sprites.north = sprite;
			else if (ft_strcmp(split[0], "WE"))
				game.sprites.west = sprite;
			else if (ft_strcmp(split[0], "SO"))
				game.sprites.south = sprite;
			else if (ft_strcmp(split[0], "EA"))
				game.sprites.east = sprite;
			sprites_i += 1;
		}
		else
		{
			t_color color = (t_color){ft_atoi(split[1]), ft_atoi(split[2]), ft_atoi(split[3])};
			if (*split[0] == 'C')
				game.colors.ceil = color;
			else if (*split[0] == 'F')
				game.colors.floor = color;
			colors_i += 1;
		}
		free(split);
		buffer += 1;
	}
	game.map = buffer;
	return (game);
}

void	free_game(t_game *game)
{
	if (game->map)
		free_2Darrays(game->map);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		free(game->mlx);
	}
}

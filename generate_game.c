/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/18 12:37:42 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	get_cardinal_direction(const char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_cardinal_direction(map[i][j]))
				return (map[i][j]);
			j += 1;
		}
		i += 1;
	}
}

static void	init_sprites(t_game *game, const char *c_dir, const char *path)
{
	int		w;
	int		h;
	void	*sprite;

	w = WIDTH;
	h = HEIGHT;
	sprite = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (ft_strcmp(c_dir, "NO") == 0
		|| ft_strcmp(c_dir, "N") == 0)
		game->sprites.north = sprite;
	else if (ft_strcmp(c_dir, "WE") == 0
		|| ft_strcmp(c_dir, "W") == 0)
		game->sprites.west = sprite;
	else if (ft_strcmp(c_dir, "SO") == 0
		|| ft_strcmp(c_dir, "S") == 0)
		game->sprites.south = sprite;
	else if (ft_strcmp(c_dir, "EA") == 0
		|| ft_strcmp(c_dir, "E") == 0)
		game->sprites.east = sprite;
}

static void	init_colors(t_game *game, char **split)
{
	t_color	color;

	color = (t_color){ft_atoi(split[1]), ft_atoi(split[2]), ft_atoi(split[3])};
	if (*split[0] == 'C')
		game->colors.ceil = color;
	else if (*split[0] == 'F')
		game->colors.floor = color;
}

t_game	generate_game(char **buffer)
{
	t_game	game;
	size_t	settings_i;
	char	**split;

	settings_i = 0;
	while (settings_i < N_SETTINGS)
	{
		split = ft_split(*buffer, ' ');
		free(*buffer);
		if (!split[2])
			init_sprites(&game, split[0], split[1]);
		else
			init_colors(&game, split);
		free_2Darrays(split);
		buffer += 1;
		settings_i += 1;
	}
	game.map = buffer;
	game.cardinal_direction = get_cardinal_direction(buffer);
	return (game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:56:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/05/21 19:58:52 by pemiguel         ###   ########.fr       */
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
	return ('\0');
}

static void	init_sprites(t_game *game, char *c_dir, char *path)
{
	int		w;
	int		h;
	void	*sprite;

	w = WIDTH;
	h = HEIGHT;
	sprite = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (ft_strcmp(c_dir, "NO") == 0
		|| ft_strcmp(c_dir, "N") == 0)
		game->sprites.north = create_textures(sprite);
	else if (ft_strcmp(c_dir, "WE") == 0
		|| ft_strcmp(c_dir, "W") == 0)
		game->sprites.west = create_textures(sprite);
	else if (ft_strcmp(c_dir, "SO") == 0
		|| ft_strcmp(c_dir, "S") == 0)
		game->sprites.south = create_textures(sprite);
	else if (ft_strcmp(c_dir, "EA") == 0
		|| ft_strcmp(c_dir, "E") == 0)
		game->sprites.east = create_textures(sprite);
}

static void	init_colors(t_game *game, char *codes, char type)
{
	t_color	color;
	char	**rgb_codes;

	rgb_codes = ft_split(codes, ',');
	color = (t_color){ft_atoi(rgb_codes[0]), ft_atoi(rgb_codes[1]), ft_atoi(rgb_codes[2])};
	if (type == 'C')
		game->colors.ceil = color;
	else if (type == 'F')
		game->colors.floor = color;
	free_2Darrays(rgb_codes);
}

t_game	generate_game(char **buffer)
{
	t_game	game;
	size_t	settings_i;
	char	**split;

	start_window(&game);
	settings_i = 0;
	while (settings_i < N_SETTINGS)
	{
		split = ft_split(*buffer, ' ');
		free(*buffer);
		if (is_color(*split[0]))
			init_colors(&game, split[1], *split[0]);
		else
			init_sprites(&game, split[0], split[1]);
		free_2Darrays(split);
		buffer += 1;
		settings_i += 1;
	}
	game.map = buffer;
	game.cardinal_direction = get_cardinal_direction((const char **)buffer);
	return (game);
}

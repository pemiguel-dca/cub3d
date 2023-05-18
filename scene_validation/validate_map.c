/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:24:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 12:07:07 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	right_wall(const char **map, size_t i, size_t j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (true);
		j += 1;
	}
	return (false);
}

static bool	left_wall(const char **map, size_t i, size_t j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (true);
		j -= 1;
	}
	return (false);
}

static bool	down_wall(const char **map, size_t i, size_t j)
{
	while (map[i])
	{
		if (map[i][j] == '1')
			return (true);
		if (map[i + 1] && j >= ft_strlen(map[i + 1]))
			return (false);
		i += 1;
	}
	return (false);
}

static bool	up_wall(const char **map, int i, size_t j)
{
	while (i != -1)
	{
		if (map[i][j] == '1')
			return (true);
		if (i - 1 > 0 && j >= ft_strlen(map[i - 1]))
			return (false);
		i -= 1;
	}
	return (false);
}

static bool	surrounded_by_walls(const char **map, size_t y, size_t x)
{
	if (x == get_first_occur_row(map, y)
		|| x == get_last_occur_row(map, y)
		|| y == 0 || y == get_cols(map) - 1)
		return (false);
	if (!right_wall(map, y, x) || !left_wall(map, y, x)
		|| !up_wall(map, y, x) || !down_wall(map, y, x))
		return (false);
	return (true);
}

bool	valid_map(const char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0'
				|| is_cardinal_direction(map[i][j]))
				&& !surrounded_by_walls(map, i, j))
					return (error_msg(MAP_WALLS));
			j += 1;
		}
		i += 1;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:24:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:18:06 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	right_wall(const char **map, size_t i, size_t j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (true);
		j += 1;
	}
	return (false);
}

bool	left_wall(const char **map, size_t i, size_t j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (true);
		j -= 1;
	}
	return (false);
}

bool	down_wall(const char **map, size_t i, size_t j)
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

bool	up_wall(const char **map, int i, size_t j)
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

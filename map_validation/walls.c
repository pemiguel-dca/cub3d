/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:24:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/16 19:48:36 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	right_wall(const t_game *game, size_t i, size_t j)
{
	while (game->map[i][j])
	{
		if (game->map[i][j] == '1')
			return (true);
		j += 1;
	}
	return (false);
}

static bool	left_wall(const t_game *game, size_t i, size_t j)
{
	while (game->map[i][j])
	{
		if (game->map[i][j] == '1')
			return (true);
		j -= 1;
	}
	return (false);
}

static bool	down_wall(const t_game *game, size_t i, size_t j)
{
	while (game->map[i])
	{
		if (game->map[i][j] == '1')
			return (true);
		if (game->map[i + 1] && j >= ft_strlen(game->map[i + 1]))
			return (false);
		i += 1;
	}
	return (false);
}

static bool	up_wall(const t_game *game, int i, size_t j)
{
	while (i != -1)
	{
		if (game->map[i][j] == '1')
			return (true);
		if (i - 1 > 0 && j >= ft_strlen(game->map[i - 1]))
			return (false);
		i -= 1;
	}
	return (false);
}

bool	check_walls(const t_game *game, size_t y, size_t x)
{
	/*extremidades*/
	if (x == get_first_occur_row(game, y)
		|| x == get_last_occur_row(game, y)
		|| y == 0 || y == get_cols((const char **)game->map) - 1)
		return (false);
	if (!right_wall(game, y, x) || !left_wall(game, y, x)
		|| !up_wall(game, y, x) || !down_wall(game, y, x))
		return (false);
	return (true);
}

bool	surrounded_by_walls(const t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if ((game->map[i][j] == '0'
				|| is_cardinal_direction(game->map[i][j]))
				&& !check_walls(game, i, j))
					return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}

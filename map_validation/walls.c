/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:24:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 21:20:58 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*make more tests to check if any of this functions has a SEGV (read)*/

static bool	rigth_wall(const t_game *game, size_t i, size_t j)
{
	if (j == ft_strlen(game->map[i]) - 1)
		return (false);
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
	if (j == get_first_occur_row(game, i))
		return (false);
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
	if (i == 0 || i == get_cols(game->map) - 1)
		return (false);
	while (game->map[i])
	{
		if (game->map[i][j] == '1')
			return (true);
		i += 1;
	}
	return (false);
}

static bool	up_wall(const t_game *game, int i, size_t j)
{
	if (i == 0 || i == get_cols(game->map) - 1)
		return (false);
	while (i != -1)
	{
		if (i - 1 > 0 && j >= ft_strlen(game->map[i - 1]))
			return (false);
		else if (game->map[i][j] == '1')
			return (true);
		i -= 1;
	}
	return (false);
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
			if (game->map[i][j] == '0'
				|| is_cardinal_direction(game->map[i][j]))
			{
				if (!rigth_wall(game, i, j) || !left_wall(game, i, j)
					|| !up_wall(game, i, j) || !down_wall(game, i, j))
					return (false);
			}
			j += 1;
		}
		i += 1;
	}
	return (true);
}

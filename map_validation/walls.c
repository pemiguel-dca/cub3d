/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:24:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 12:36:48 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*make more tests to check if any of this functions has a SEGV (read)*/

static bool	rigth_wall(t_game *game, size_t i, size_t j)
{
	if (j == ft_strlen(game->buffer[i]) - 1)
		return (false);
	while (game->buffer[i][j])
	{
		if (game->buffer[i][j] == '1')
			return (true);
		j += 1;
	}
	return (false);
}

static bool	left_wall(t_game *game, size_t i, size_t j)
{
	if (j == get_first_occur_row(game, i))
		return (false);
	while (game->buffer[i][j])
	{
		if (game->buffer[i][j] == '1')
			return (true);
		j -= 1;
	}
	return (false);
}

static bool	down_wall(t_game *game, size_t i, size_t j)
{
	if (i == 0 || i == game->cols - 1)
		return (false);
	while (game->buffer[i])
	{
		if (game->buffer[i][j] == '1')
			return (true);
		i += 1;
	}
	return (false);
}

static bool	up_wall(t_game *game, int i, size_t j)
{
	if (i == 0 || i == game->cols - 1)
		return (false);
	while (i != -1)
	{
		if (i - 1 > 0 && j >= ft_strlen(game->buffer[i - 1]))
			return (false);
		else if (game->buffer[i][j] == '1')
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
	while (game->buffer[i])
	{
		j = 0;
		while (game->buffer[i][j])
		{
			if (game->buffer[i][j] == '0'
				|| is_cardinal_direction(game->buffer[i][j]))
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

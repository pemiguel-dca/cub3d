/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:26:45 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/14 16:57:31 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline bool	can_move(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (game->buffer[i])
	{
		j = 0;
		while (game->buffer[i][j])
		{
			if (is_cardinal_direction(game->buffer[i][j])
				&& (game->buffer[i][j + 1] == '0'
				|| game->buffer[i][j - 1] == '0'
				|| game->buffer[i + 1][j] == '0'
				||game->buffer[i - 1][j] == '0'))
				return (true);
			j += 1;
		}
		i += 1;
	}
	return (false);
}

bool	is_valid_map(t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	c_directions;

	if (!game->buffer || !validate_identifiers(game)
		|| !surrounded_by_walls(game))
		return (false);
	i = 0;
	c_directions = 0;
	while (game->buffer[i])
	{
		j = 0;
		while (game->buffer[i][j])
		{
			if (!verify_char(game->buffer[i][j]))
				return (false);
			if (is_cardinal_direction(game->buffer[i][j]))
				c_directions += 1;
			j += 1;
		}
		i += 1;
	}
	if (c_directions != 1 || (c_directions == 1 && !can_move(game)))
		return (false);
	return (true);
}

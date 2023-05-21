/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:30 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/21 15:31:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "cub3d.h"
#include "raycaster.h"

static inline t_vec2	player_pos(const char **map)
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
				return ((t_vec2){.x = j, .y = i});
			j += 1;
		}
		i += 1;
	}
	return ((t_vec2){.x = 0, .y = 0});
}

void	init_player(t_game *game);

#endif

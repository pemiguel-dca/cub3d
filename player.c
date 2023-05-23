/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:10:41 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/23 15:10:36 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	north_pov(t_player *player)
{
	player->dir = write_vector(0, -1);
	player->camera_plane = write_vector(0.66, 0);
}

static void	south_pov(t_player *player)
{
	player->dir = write_vector(0, 1);
	player->camera_plane = write_vector(-0.5, 0);
}

static void	east_pov(t_player *player)
{
	player->dir = write_vector(1, 0);
	player->camera_plane = write_vector(0, 0.5);
}

static void	west_pov(t_player *player)
{
	player->dir = write_vector(-1, 0);
	player->camera_plane = write_vector(0, -0.5);
}

void	init_player(t_game *game)
{
	game->player.pos = player_pos((const char **)game->map);
	add_to_vector(&game->player.pos, 0.5);
	if (game->cardinal_direction == 'N')
		north_pov(&game->player);
	else if (game->cardinal_direction == 'S')
		south_pov(&game->player);
	else if (game->cardinal_direction == 'E')
		east_pov(&game->player);
	else if (game->cardinal_direction == 'W')
		west_pov(&game->player);
}

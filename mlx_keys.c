/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:00:24 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/22 14:59:10 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#define ROTATION_SPEED 0.01
#define MOVE_SPEED 0.05

int	top_right(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	keys_pressed(int key, t_game *game)
{
	/**/
	t_vec2	old_player_dir;
	t_vec2	old_camera_plane;

	old_player_dir = game->player.dir;
	old_camera_plane= game->player.camera_plane;
	if (key == ESC)
	{
		free_game(game);
		exit(EXIT_SUCCESS);
	}
	if (key == W)
	{
		if (game->map[(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)][(int)game->player.pos.y])
			game->player.pos.x += game->player.dir.x * MOVE_SPEED;
		if (game->map[(int)game->player.pos.x][(int)(game->player.pos.y + game->player.dir.y * MOVE_SPEED)])
			game->player.pos.y += game->player.dir.y * MOVE_SPEED;
	}
	if (key == RIGTH_ARROW)
	{
		game->player.dir.x = game->player.dir.x * cos(-ROTATION_SPEED)
		- game->player.dir.y * sin(-ROTATION_SPEED);
		game->player.dir.y = old_player_dir.x * sin(-ROTATION_SPEED)
		+ game->player.dir.y * cos(-ROTATION_SPEED);
		game->player.camera_plane.x = game->player.camera_plane.x * cos(-ROTATION_SPEED)
		- game->player.camera_plane.y * sin(ROTATION_SPEED);
		game->player.camera_plane.x += old_camera_plane.x * sin(-ROTATION_SPEED)
		+ game->player.camera_plane.y * cos(ROTATION_SPEED);
	}
	start(game);
	return (0);
}

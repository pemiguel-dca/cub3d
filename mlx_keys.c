/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:00:24 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/22 18:11:41 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"
#include <math.h>

#define ROTATION_SPEED 0.1
#define MOVE_SPEED 0.05

int	top_right(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	keys_pressed(int key, t_game *game)
{
	t_vec2	old_player_dir;
	t_vec2	old_camera_plane;

	old_player_dir = game->player.dir;
	old_camera_plane = game->player.camera_plane;

	if (key == ESC)
	{
		free_game(game);
		exit(EXIT_SUCCESS);
	}
	// TODO W and S aren't working and disregard direction facing
	else if (key == W)
    {
        if ((int)game->player.pos.x - 1 > 0
            && game->map[(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)]
            [(int)game->player.pos.y])
            game->player.pos.x += game->player.dir.x * MOVE_SPEED;
        if ((int)game->player.pos.y - 1 > 0
            && game->map[(int)game->player.pos.x]
            [(int)(game->player.pos.y + game->player.dir.y * MOVE_SPEED)])
            game->player.pos.y += game->player.dir.y * MOVE_SPEED;
    }
    else if (key == S)
    {
        if ((int)game->player.pos.x + 1 < ft_strlen((const char **)game->map[(int)game->player.pos.y])
            && game->map[(int)(game->player.pos.x + game->player.dir.x * MOVE_SPEED)]
            [(int)game->player.pos.y])
            game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
        if ((int)game->player.pos.y + 1 < get_cols((const char **)game->map)
            && game->map[(int)game->player.pos.x]
            [(int)(game->player.pos.y + game->player.dir.y * MOVE_SPEED)])
            game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
    }
	else if (key == LEFT_ARROW)
	{
		game->player.dir.x = game->player.dir.x * cos(-ROTATION_SPEED)
		- game->player.dir.y * sin(-ROTATION_SPEED);
		game->player.dir.y = old_player_dir.x * sin(-ROTATION_SPEED)
		+ game->player.dir.y * cos(-ROTATION_SPEED);

		game->player.camera_plane.x = game->player.camera_plane.x * cos(-ROTATION_SPEED)
		- game->player.camera_plane.y * sin(-ROTATION_SPEED);
		game->player.camera_plane.y = old_camera_plane.x * sin(-ROTATION_SPEED)
		+ game->player.camera_plane.y * cos(-ROTATION_SPEED);
	}
	else if (key == RIGHT_ARROW)
	{
		game->player.dir.x = game->player.dir.x * cos(ROTATION_SPEED)
		- game->player.dir.y * sin(ROTATION_SPEED);
		game->player.dir.y = old_player_dir.x * sin(ROTATION_SPEED)
		+ game->player.dir.y * cos(ROTATION_SPEED);

		game->player.camera_plane.x = game->player.camera_plane.x * cos(ROTATION_SPEED)
		- game->player.camera_plane.y * sin(ROTATION_SPEED);
		game->player.camera_plane.y = old_camera_plane.x * sin(ROTATION_SPEED)
		+ game->player.camera_plane.y * cos(ROTATION_SPEED);
	}
	start(game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:00:24 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 13:06:30 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "raycaster.h"
#include "rotate.h"

int	exit_game(t_game *game)
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
		exit_game(game);
	else if (key == W)
		move_foward(game);
	else if (key == A)
		move_left(game);
	else if (key == S)
		move_backwards(game);
	else if (key == D)
		move_right(game);
	else if (key == LEFT_ARROW)
		rotate_left(game, old_player_dir, old_camera_plane);
	else if (key == RIGHT_ARROW)
		rotate_right(game, old_player_dir, old_camera_plane);
	start(game);
	return (0);
}

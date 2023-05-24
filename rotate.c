/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:48:55 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:59:52 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotate.h"

void	rotate_left(t_game *game, t_vec2 old_player_dir,
			t_vec2 old_camera_plane)
{
	game->player.dir.x = game->player.dir.x * cos(ROTATION_SPEED)
		- game->player.dir.y * sin(-ROTATION_SPEED);
	game->player.dir.y = old_player_dir.x * sin(-ROTATION_SPEED)
		+ game->player.dir.y * cos(ROTATION_SPEED);
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos(ROTATION_SPEED) - game->player.camera_plane.y
		* sin(-ROTATION_SPEED);
	game->player.camera_plane.y = old_camera_plane.x * sin(-ROTATION_SPEED)
		+ game->player.camera_plane.y * cos(ROTATION_SPEED);
}

void	rotate_right(t_game *game, t_vec2 old_player_dir,
			t_vec2 old_camera_plane)
{
	game->player.dir.x = game->player.dir.x * cos(ROTATION_SPEED)
		- game->player.dir.y * sin(ROTATION_SPEED);
	game->player.dir.y = old_player_dir.x * sin(ROTATION_SPEED)
		+ game->player.dir.y * cos(ROTATION_SPEED);
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos(ROTATION_SPEED) - game->player.camera_plane.y
		* sin(ROTATION_SPEED);
	game->player.camera_plane.y = old_camera_plane.x * sin(ROTATION_SPEED)
		+ game->player.camera_plane.y * cos(ROTATION_SPEED);
}

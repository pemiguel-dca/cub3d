/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:42:46 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:57:45 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

void	move_foward(t_game *game)
{
	if (game->map[(int)(game->player.pos.y)][(int)(game->player.pos.x
		+ game->player.dir.y * MOVE_SPEED)] != '1')
		game->player.pos.x += game->player.dir.x * MOVE_SPEED;
	if (game->map[(int)(game->player.pos.y + game->player.dir.y
			* MOVE_SPEED)][(int)(game->player.pos.x)] != '1')
		game->player.pos.y += game->player.dir.y * MOVE_SPEED;
}

void	move_backwards(t_game *game)
{
	if (game->map[(int)(game->player.pos.y)]
		[(int)(game->player.pos.x - game->player.dir.x * MOVE_SPEED)] != '1')
		game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
	if (game->map[(int)(game->player.pos.y - game->player.dir.y * MOVE_SPEED)]
		[(int)(game->player.pos.x)] != '1')
		game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
}

void	move_left(t_game *game)
{
	if (game->map[(int)(game->player.pos.y)]
		[(int)(game->player.pos.x + game->player.dir.y * MOVE_SPEED)] != '1')
		game->player.pos.x += game->player.dir.y * MOVE_SPEED;
	if (game->map[(int)(game->player.pos.y - game->player.dir.x * MOVE_SPEED)]
		[(int)(game->player.pos.x)] != '1')
		game->player.pos.y -= game->player.dir.x * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	if (game->map[(int)(game->player.pos.y)]
		[(int)(game->player.pos.x - game->player.dir.y * MOVE_SPEED)] != '1')
		game->player.pos.x -= game->player.dir.y * MOVE_SPEED;
	if (game->map[(int)(game->player.pos.y + game->player.dir.x * MOVE_SPEED)]
		[(int)(game->player.pos.x)] != '1')
		game->player.pos.y += game->player.dir.x * MOVE_SPEED;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 20:57:29 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

inline static void	__debug_vector(const t_vec2 *vec)
{
	printf("t_vec2{.x = %f, .y = %f}\n", vec->x, vec->y);
}

static t_vec2	player_pos(const char **buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i][j])
		{
			if (is_cardinal_direction(buffer[i][j]))
				return ((t_vec2){.x = j, .y = i});
			j += 1;
		}
		i += 1;
	}
	return ((t_vec2){.x = 0, .y = 0});
}

// https://www.youtube.com/watch?v=gYRrGTC7GtA 2:00
// https://lodev.org/cgtutor/raycasting.html
void	start(t_game *game)
{
	// player positin
	t_vec2		player = player_pos(game->map);
	// go north
	t_vec2		ray_direction = {-1, 0};
	// still not entirely sure how this works
	t_vec2		ray_unit_step_size = {
		sqrt(1 + (ray_direction.y / ray_direction.x) * (ray_direction.y / ray_direction.x)),
		sqrt(1 + (ray_direction.x / ray_direction.y) * (ray_direction.x / ray_direction.y))
	};

	t_vec2	vMapCheck = player;
	t_vec2	vRayLength1D;
	t_vec2	step;

	// still not entirely sure how this works
	// Establish Starting Conditions
	if (ray_direction.x < 0)
	{
		step.x = -1;
		vRayLength1D.x = (player.x + 1 - vMapCheck.x) * ray_unit_step_size.x;
	}
	else
	{
		step.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1 - player.x) * ray_unit_step_size.x;
	}

	if (ray_direction.y < 0)
	{
		step.y = -1;
		vRayLength1D.y = (player.y + 1 - vMapCheck.y) * ray_unit_step_size.y;
	}
	else
	{
		step.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1 - player.y) * ray_unit_step_size.y;
	}

	bool tile_found = false;
	double distance = 0;

	while (!tile_found)
	{
		// still not entirely sure how this works
		// Walk along shortest path
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += step.x;
			distance = vRayLength1D.x;
			vRayLength1D.x += ray_unit_step_size.x;
		}
		else
		{
			vMapCheck.y += step.y;
			distance = vRayLength1D.y;
			vRayLength1D.y += ray_unit_step_size.y;
		}

		// __debug_vector(&vMapCheck);

		// if bumped into wall
		if (game->map[(int)vMapCheck.y][(int)vMapCheck.x] == '1')
		{
			tile_found = true;
		}
	}

	// initial pos (player) + (direction * distance)
	t_vec2	intersection = vec_add(player, (t_vec2){ray_direction.x * distance, ray_direction.y * distance});

	__debug_vector(&intersection);

	/*
	unsigned int	stripe = 0;

	while (stripe < WIDTH)
	{
		t_vec2 player = player_pos(game->map);

		stripe += 1;
	}
	*/
}

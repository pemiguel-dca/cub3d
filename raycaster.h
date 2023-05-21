/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/21 15:32:40 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdio.h>
# include <math.h>
# include "cub3d.h"

typedef struct
{
	t_vec2	ray_dir;
	t_vec2	camera;
	t_vec2	curr_ray_square;
	double		ray_distance_to_wall; //perpendicular distance to the wall (not Euclidean)
}	t_raycaster;

/*check out https://www.youtube.com/watch?v=NbSee-XM7WA to understand DDA algorithm*/

typedef	struct
{
	t_vec2	length_to_first_step; //length of ray from current position to next x or y-side
	t_vec2	length_to_next_step; //length of ray from one x or y-side to next x or y-side
	t_vec2	step; //take a step in which direction(+1x for right, -1y for up, -1x for left, +1y for down)
	bool		hit_wall;
	size_t		hit_side;
}	t_dda;

static inline t_vec2	write_vector(double x, double y)
{
	return ((t_vec2){.x = x, .y = y});
}

static inline t_vec2 add_to_vector(t_vec2 *v, double value)
{
	v->x += value;
	v->y += value;
}

static inline t_vec2 mult_vector(t_vec2 v1, double value)
{
	t_vec2	result;

	result.x = v1.x * value;
	result.y = v1.y * value;
	return (result);
}

void	start(t_game *game);

#endif

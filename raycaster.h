/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:38:32 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdio.h>
# include <math.h>
# include "cub3d.h"

typedef struct raycaster
{
	t_vec2	ray_dir;
	t_vec2	camera;
	t_vec2	curr_ray_square;
	double	ray_distance_to_wall;
}	t_raycaster;

typedef struct dda
{
	t_vec2	length_to_first_step;
	t_vec2	length_to_next_step;
	t_vec2	step;
	bool	hit_wall;
	size_t	hit_side;
}	t_dda;

static inline t_vec2	write_vector(double x, double y)
{
	return ((t_vec2){.x = x, .y = y});
}

static inline void	add_to_vector(t_vec2 *v, double value)
{
	v->x += value;
	v->y += value;
}

static inline t_vec2	mult_vector(t_vec2 v1, double value)
{
	t_vec2	result;

	result.x = v1.x * value;
	result.y = v1.y * value;
	return (result);
}

void	start(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 16:01:48 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <stdio.h>
# include <math.h>

/*The FOV is determinated by the ratio of the length of the direction vector,
and the length of the camera_plane

Later on when rotating around with the input keys, the values of dir and plane will be changed,
but they'll always remain perpendicular and keep the same length

*/
typedef struct
{
	double	x;
	double	y;
}	t_vector;


typedef struct
{
	t_vector	player_dir;
	t_vector	player_pos;
	t_vector	player_camera_plane;
	t_vector	ray_dir;
	t_vector	camera;
	t_vector	curr_ray_square;
	int			fov;
}	t_raycaster;

t_raycaster	*init_rc(const char **buffer);

static inline t_vector	init_vector(double x, double y)
{
	return ((t_vector){.x = x, .y = y});
}

/*Operations with 'vectors'*/
static inline t_vector add_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

static inline t_vector sub_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return (result);
}

static inline t_vector mul_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	return (result);
}

static inline t_vector div_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	return (result);
}

#endif

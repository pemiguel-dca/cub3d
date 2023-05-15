/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 12:23:13 by pemiguel         ###   ########.fr       */
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
	int			fov;
}	t_raycaster;


static inline	bzero_vector(t_vector *v)
{
	*v = (t_vector){.x = 0, .y = 0};
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

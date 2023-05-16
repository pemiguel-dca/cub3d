/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/16 15:11:10 by pemiguel         ###   ########.fr       */
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
	size_t		fov;
}	t_raycaster;

/*check out https://www.youtube.com/watch?v=NbSee-XM7WA to understand DDA algorithm*/

typedef	struct
{
	t_vector	length_until_next_square;
	t_vector	length_to_next_square;
	double		length_ray;
	t_vector	step; //take a step in which direction(+1x for right, +1y for up, -1x for left, -1y for down)
	bool		hit_wall;
	size_t		hit_side; //if x side of square was it = 1, if y side = 0
}	t_dda;

t_raycaster	*init_rc(const char **buffer);

static inline t_vector	write_vector(double x, double y)
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

/* meter esta merda direito dps */

static bool is_cardinal_directionfodase(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static inline t_vector	player_pos(const char **buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i][j])
		{
			if (is_cardinal_directionfodase(buffer[i][j]))
				break ;
			j += 1;
		}
		i += 1;
	}
	return ((t_vector){.x = j, .y = i});
}

/* */

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:21:59 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 12:45:20 by pemiguel         ###   ########.fr       */
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
	t_vector	player_dir; //where player is loolookingking
	t_vector	player_pos;
	t_vector	player_camera_plane;
	t_vector	ray_dir;
	t_vector	camera;
	t_vector	curr_ray_square;
	size_t		fov;
	double		ray_distance_to_wall; //perpendicular distance to the wall (not Euclidean)
}	t_raycaster;

/*check out https://www.youtube.com/watch?v=NbSee-XM7WA to understand DDA algorithm*/

typedef	struct
{
	t_vector	length_to_first_step; //length of ray from current position to next x or y-side
	t_vector	length_to_next_step; //length of ray from one x or y-side to next x or y-side
	t_vector	step; //take a step in which direction(+1x for right, +1y for up, -1x for left, -1y for down)
	bool		hit_wall;
	size_t		hit_side;
}	t_dda;

typedef struct
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw;

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
			if (is_cardinal_direction(buffer[i][j]))
				break ;
			j += 1;
		}
		i += 1;
	}
	return ((t_vector){.x = j, .y = i});
}

static inline t_vector	write_vector(double x, double y)
{
	return ((t_vector){.x = x, .y = y});
}

static inline t_vector add_vectors(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

#endif

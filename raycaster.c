/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/16 15:48:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

t_raycaster	*init_rc(const char **buffer)
{
	t_raycaster	*rc;

	if (!buffer)
		return (NULL);
	rc = malloc(sizeof(t_raycaster));
	rc->player_pos = player_pos(buffer);
	rc->player_dir = write_vector(-1, 0);
	rc->player_camera_plane = write_vector(0, 0.66);
	rc->fov = 66;
	return (rc);
}

/*
camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0,
and the left side of the screen gets coordinate -1.

*/

void	calc_ray(t_game *game)
{
	size_t		stripe;
	t_vector	tmp;
	t_raycaster	*rc;
	t_dda		dda;

	stripe = 0;
	rc = game->rc;
	/*The ray starts at the position of the player (player_pos).*/
	tmp = add_vectors(rc->player_dir, rc->player_camera_plane);
	while (stripe < get_cols(game) - 1)/*For every vertical stripe of the screen*/
	{
		/*camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents(1 for right side, 0 for middle, -1 for left)*/
		rc->camera.x = 2 * stripe / (get_cols(game) - 1);
		rc->ray_dir.x = tmp.x * stripe;
		rc->ray_dir.y = tmp.y * stripe;
		/*curr_ray_square represent the current square of the map the ray is in.*/
		rc->curr_ray_square = write_vector((int)rc->player_pos.x, (int)rc->player_pos.y);

		dda.length_to_next_square = write_vector(abs(1 / rc->ray_dir.x), abs(1 / rc->ray_dir.y));

		
		stripe += 1;
	}
}

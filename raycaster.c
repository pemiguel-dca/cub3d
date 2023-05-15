/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 17:09:41 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

t_raycaster	*init_rc(const char **buffer)
{
	t_raycaster	*rc;

	if (!buffer)
		return (NULL);
	rc = malloc(sizeof(t_raycaster *));
	rc->player_pos = player_pos(buffer);
	rc->player_dir = init_vector(-1, 0);
	rc->player_camera_plane = init_vector(0, 0.66);
	return (rc);
}

/*
camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0,
and the left side of the screen gets coordinate -1.

curr_ray_square represent the current square of the map the ray is in.
*/

void	calc_ray(t_game *game)
{
	size_t		i;
	t_vector	tmp;
	t_raycaster	*rc;

	i = 0;
	tmp = add_vectors(rc->player_dir, rc->player_camera_plane);
	rc = game->rc;
	while (i < game->cols)
	{
		rc->camera.x = 2 * i / (double)WIDTH - 1;
		rc->ray_dir.x = tmp.x * i;
		rc->ray_dir.y = tmp.y * i;
		rc->curr_ray_square = init_vector((int)rc->player_pos.x, (int)rc->player_pos.y);
		i += 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/19 17:12:04 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

static inline void __debug_vector(const t_vec2 *vec)
{
	printf("t_vector{.x = %f, .y = %f}\n", vec->x, vec->y);

}

t_draw	*get_draw_properties(t_raycaster *rc, t_dda *dda)
{
	t_draw	*draw;

	draw = malloc(sizeof(t_draw *));
	if (!draw)
		return (NULL);
	/*Calculate the ray distance to the wall that was hit, depending on which side*/
	if (dda->hit_side == 0)
		rc->ray_distance_to_wall = dda->length_to_first_step.x - dda->length_to_next_step.x;
	else
		rc->ray_distance_to_wall = dda->length_to_first_step.y - dda->length_to_next_step.y;
	printf("ray distance to wall: %f\n", rc->ray_distance_to_wall);
	draw->line_height = (int)(HEIGHT / rc->ray_distance_to_wall);
	printf("line_height: %d\n", draw->line_height);
	/*Find the lowest pixel and the highest pixel to fill in the curr stripe*/
	draw->draw_start = -draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	return (draw);
}

void	dda_algo(t_raycaster *rc, t_dda *dda, const char **map)
{
	/*Basically we will step in the due direction until we hit a wall (again see the video for deeper understanding)*/
	while (!dda->hit_wall)
	{
		/*Here we will see which step is bigger and take that respective step*/
		/*So in this case we will take a step in x direction
		If x side of square was it then hit_side = 0, if y side was hit, hit_side = 1*/
		if (dda->length_to_first_step.x > dda->length_to_first_step.y)
		{
			dda->length_to_first_step.x += dda->length_to_next_step.x;
			rc->curr_ray_square.x += dda->step.x;
			dda->hit_side = 0;
		}
		/*Step in y direction*/
		else
		{
			dda->length_to_first_step.y += dda->length_to_next_step.y;
			rc->curr_ray_square.y += dda->step.y;
			dda->hit_side = 1;
		}
		if (map[(int)rc->curr_ray_square.y][(int)rc->curr_ray_square.x] == '1')
			dda->hit_wall = true;
	}
}

void	step_in_which_direction(t_raycaster *rc, t_dda *dda)
{
	/*This function will calculate the direction of step and find the length to the first step
	If the ray direction has a negative x component, step.x is -1, if it as a positive x-component, step.x is 1,
	the same goes for the y component*/
	if (rc->ray_dir.x > 0)
	{
		dda->step.x = -1;
		dda->length_to_first_step.x = (rc->player_pos.x * (int)rc->curr_ray_square.x) * dda->length_to_next_step.x;
	}
	else
	{
		dda->step.x = 1;
		dda->length_to_first_step.x = ((int)rc->curr_ray_square.x + 1.0 - rc->player_pos.x) * dda->length_to_next_step.x;
	}
	if (rc->ray_dir.y > 0)
	{
		dda->step.y = -1;
		dda->length_to_first_step.y = (rc->player_pos.y * (int)rc->curr_ray_square.y) * dda->length_to_next_step.y;
	}
	else
	{
		dda->step.y = 1;
		dda->length_to_first_step.y = ((int)rc->curr_ray_square.y + 1.0 - rc->player_pos.y) * dda->length_to_next_step.y;
	}
}

static t_raycaster	init_rc(const char **map, size_t stripe)
{
	t_raycaster	rc;
	t_vec2	tmp;

/*camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0,
and the left side of the screen gets coordinate -1.*/

	rc.player_pos = player_pos(map);
	rc.player_dir = write_vector(-1, 0);
	rc.player_camera_plane = write_vector(0, 0.66);
	/*The ray starts at the position of the player (player_pos).*/
	tmp = add_vectors(rc.player_dir, rc.player_camera_plane);
	rc.fov = 66;
	rc.camera.x = 2 * stripe / (double)WIDTH;
	rc.camera.x -= 1;
	rc.ray_dir.x = tmp.x * rc.camera.x;
	rc.ray_dir.y = tmp.y * rc.camera.x;
	/*curr_ray_square represent the current square of the map the ray is in.*/
	rc.curr_ray_square = write_vector(floor(rc.player_pos.x), floor(rc.player_pos.y));
	return (rc);
}

void	start(t_game *game)
{
	size_t		stripe;
	t_raycaster	rc;
	t_dda		dda;
	t_draw		*draw_prop;

	stripe = 0;
	game->data = create_new_image(game->mlx);
	while (stripe < WIDTH)/*For every vertical stripe of the screen*/
	{
		/*camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents(1 for right side, 0 for middle, -1 for left)*/
		rc = init_rc((const char **)game->map, stripe);
		dda.hit_wall = false;
		dda.length_to_next_step = write_vector(fabs(1 / rc.ray_dir.x), fabs(1 / rc.ray_dir.y));
		step_in_which_direction(&rc, &dda);
		/*After finding in which direction where going we can perform the DDA algorithm (see video in .h file)*/
		dda_algo(&rc, &dda, (const char **)game->map);
		draw_prop = get_draw_properties(&rc, &dda);
		printf("%d %d %d\n", draw_prop->draw_start, draw_prop->draw_end, draw_prop->line_height);
		draw_vertical_line(game,draw_prop, stripe);//this function is supost to do the drawing
		free(draw_prop);
		stripe += 1;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/21 20:19:56 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static inline void __debug_vector(const t_vec2 *vec)
{
	printf("t_vector{.x = %f, .y = %f}\n", vec->x, vec->y);
}

t_draw	get_draw_properties(t_raycaster *rc, t_dda *dda)
{
	t_draw	draw;

	/*Calculate the ray distance to the wall that was hit, depending on which side
	we do this calculation (dda->length_to_first_step.x(y) - dda->length_to_next_step.x(y))
	because in the dda algo we go one step further in a wall*/
	if (dda->hit_side == 0)
		rc->ray_distance_to_wall = dda->length_to_first_step.x - dda->length_to_next_step.x;
	else
		rc->ray_distance_to_wall = dda->length_to_first_step.y - dda->length_to_next_step.y;
	draw.line_height = (int)(HEIGHT / rc->ray_distance_to_wall);
	/*Find the lowest pixel and the highest pixel to fill in the curr stripe*/
	draw.start = -draw.line_height / 2 + HEIGHT / 2;
	if (draw.start < 0)
		draw.start = 0;
	draw.end = draw.line_height / 2 + HEIGHT / 2;
	if (draw.end >= HEIGHT)
		draw.end = HEIGHT - 1;
	return (draw);
}

void	dda_algo(t_raycaster *rc, t_dda *dda, const char **map)
{
	/*Basically we will step in the due direction until we hit a wall (again see the video for deeper understanding)*/
	while (!dda->hit_wall)
	{
		/*If x side of square was it then hit_side = 0, if y side was hit, hit_side = 1*/
		if (dda->length_to_first_step.x < dda->length_to_first_step.y)
		{
			dda->length_to_first_step.x += dda->length_to_next_step.x;
			rc->curr_ray_square.x += dda->step.x;
			dda->hit_side = 0;
		}
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

void	step_in_which_direction(t_raycaster *rc, t_dda *dda, t_game *game)
{
	/*This function will calculate the direction of step and find the length to the first step
	If the ray direction has a negative x component, step.x is -1, if it as a positive x-component, step.x is 1,
	vice-versa for y component*/
	if (rc->ray_dir.x > 0)
	{
		dda->step.x = 1;
		dda->length_to_first_step.x = (game->player.pos.x - (int)rc->curr_ray_square.x) * dda->length_to_next_step.x;
	}
	else
	{
		dda->step.x = -1;
		dda->length_to_first_step.x = ((int)rc->curr_ray_square.x + 1.0f - game->player.pos.x) * dda->length_to_next_step.x;
	}
	if (rc->ray_dir.y > 0)
	{
		dda->step.y = -1;
		dda->length_to_first_step.y = (game->player.pos.y - (int)rc->curr_ray_square.y) * dda->length_to_next_step.y;
	}
	else
	{
		dda->step.y = 1;
		dda->length_to_first_step.y = ((int)rc->curr_ray_square.y + 1.0f - game->player.pos.y) * dda->length_to_next_step.y;
	}
}

static void	init_rc(t_game *game, t_raycaster *rc, size_t stripe)
{
	/*camera.x is the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
	done this way so that the right side of the screen will get coordinate 1, the center of the screen gets coordinate 0,*/
	rc->camera.x = 2 * stripe / (double)WIDTH - 1;
	/*Error was here since I was adding before the multiplication*/
	rc->ray_dir = (t_vec2){.x = game->player.dir.x + game->player.camera_plane.x * rc->camera.x,
	.y = game->player.dir.y + game->player.camera_plane.y * rc->camera.x};
	/*curr_ray_square represent the current square of the map the ray is in.*/
	rc->curr_ray_square = write_vector(floor(game->player.pos.x), floor(game->player.pos.y));
}

size_t	get_texture_x(t_raycaster *rc, t_dda *dda, t_game *game)
{
	size_t	texture_x;
	double	wall_x;

	if (dda->hit_side)//hit a horizontal wall
		wall_x = (int)game->player.pos.x + rc->ray_distance_to_wall * rc->ray_dir.x;
	else
		wall_x = (int)game->player.pos.y + rc->ray_distance_to_wall * rc->ray_dir.y;
	/*To get the offset within the wall square we subtract the integer part (floor wall_x)*/
	wall_x -= floor(wall_x);
	/*Get the corresponding position within the texture image by multiplying the fractional part of wall * TEXTURE_WIDTH*/
	texture_x = (wall_x * TEXTURE_WIDTH);
	return (texture_x);
}

void	start(t_game *game)
{
	size_t		stripe;
	t_raycaster	rc;
	t_dda		dda;

	stripe = 0;
	game->data = create_new_image(game->mlx);
	init_player(game);
	while (stripe < WIDTH)
	{
		init_rc(game, &rc, stripe);
		dda.hit_wall = false;
		dda.length_to_next_step = write_vector(fabs(1 / rc.ray_dir.x), fabs(1 / rc.ray_dir.y));
		step_in_which_direction(&rc, &dda, game);
		/*After finding in which direction where going we can perform the DDA algorithm (see video in .h file)*/
		dda_algo(&rc, &dda, (const char **)game->map);
		draw_stripe(game, get_draw_properties(&rc, &dda), stripe, get_texture_x(&rc, &dda, game));
		stripe += 1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

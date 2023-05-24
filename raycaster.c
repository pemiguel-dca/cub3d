/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:07:37 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 12:37:07 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "texture.h"

t_draw	get_draw_properties(t_raycaster *rc, t_dda *dda)
{
	t_draw	draw;

	if (dda->hit_side == 0)
		rc->ray_distance_to_wall = dda->length_to_first_step.x
			- dda->length_to_next_step.x;
	else
		rc->ray_distance_to_wall = dda->length_to_first_step.y
			- dda->length_to_next_step.y;
	draw.line_height = (int)(HEIGHT / rc->ray_distance_to_wall);
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
	while (!dda->hit_wall)
	{
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
	if (rc->ray_dir.x > 0)
	{
		dda->step.x = 1;
		dda->length_to_first_step.x = (game->player.pos.x
				- (int)rc->curr_ray_square.x) * dda->length_to_next_step.x;
	}
	else
	{
		dda->step.x = -1;
		dda->length_to_first_step.x = ((int)rc->curr_ray_square.x + 1.0f
				- game->player.pos.x) * dda->length_to_next_step.x;
	}
	if (rc->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->length_to_first_step.y = (game->player.pos.y
				- (int)rc->curr_ray_square.y) * dda->length_to_next_step.y;
	}
	else
	{
		dda->step.y = 1;
		dda->length_to_first_step.y = ((int)rc->curr_ray_square.y + 1.0f
				- game->player.pos.y) * dda->length_to_next_step.y;
	}
}

static void	init_rc(t_game *game, t_raycaster *rc, size_t stripe)
{
	rc->camera.x = 2 * stripe / (double)WIDTH - 1;
	rc->ray_dir = (t_vec2){.x = game->player.dir.x + game->player.camera_plane.x
		* rc->camera.x, .y = game->player.dir.y
		+ game->player.camera_plane.y * rc->camera.x};
	rc->curr_ray_square = write_vector(floor(game->player.pos.x),
			floor(game->player.pos.y));
}

void	start(t_game *game)
{
	size_t		stripe;
	t_raycaster	rc;
	t_dda		dda;
	t_texture	texture;

	stripe = 0;
	game->data = create_new_image(game->mlx);
	while (stripe < WIDTH)
	{
		init_rc(game, &rc, stripe);
		dda.hit_wall = false;
		dda.length_to_next_step = write_vector(fabs(1 / rc.ray_dir.x),
				fabs(1 / rc.ray_dir.y));
		step_in_which_direction(&rc, &dda, game);
		dda_algo(&rc, &dda, (const char **)game->map);
		texture = (t_texture){.img = get_respective_texture
			(game, rc.ray_dir, dda.hit_side),
			.x = get_texture_x(&rc, &dda, game)};
		draw_stripe(game, get_draw_properties(&rc, &dda), stripe, &texture);
		stripe += 1;
	}
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
	mlx_destroy_image(game->mlx, game->data.img);
}

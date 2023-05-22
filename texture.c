/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:18:49 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/22 11:35:39 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_data	create_textures(void *sprite)
{
	t_data	data;

	data.img = sprite;
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	return (data);
}

int		get_texture_pixel(t_texture *texture)
{
	/*Convert address to integer to access the pixels within the image itself*/
	int	*pixels;

	pixels = (int *)texture->img->addr;
	return (pixels[texture->y * TEXTURE_WIDTH + texture->x]);
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

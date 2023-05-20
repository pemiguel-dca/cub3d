/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:28:21 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/20 18:55:44 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_fill_image_color(t_data *data, int w, int h, int color)
{
	char	*dst;

	dst = data->addr + (h * data->line_length + w * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_data	create_new_image(void *mlx)
{
	t_data	data;

	data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	return (data);
}

t_data	create_textures(void *sprite)
{
	t_data	data;

	data.img = sprite;
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	return (data);
}



int		get_pixel(t_data *img, int x, int y)
{
	/*Convert address to integer to access the pixels within the image itself*/
	int	*pixels;

	pixels = img->addr;
	printf("pos in pixels array: %d\n", y * TEXTURE_WIDTH + x);
    return (pixels[y * TEXTURE_WIDTH + x]);
}

void	draw_stripe(t_game *game, t_draw draw_prop, int stripe, int texture_x)
{
	size_t	i;

	i = 0;
	while (i < draw_prop.draw_start)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.ceil));
		i += 1;
	}
	/*Draw start until draw end is where we do the drawing of the textures*/
	while (i < draw_prop.draw_end)
	{
		/*Not sure if texture_y is actually correct because, instead of reading all the pixels we are reading the same exact pixel 5 times before advancing to the next one*/
		double texture_coordinate = ((double)i - draw_prop.draw_start) / draw_prop.line_height;
		/*Since we want to draw an image that's 64x64 we have to extract the color of each pixel*/ 
		int texture_y = (int)(texture_coordinate * TEXTURE_HEIGHT);
		mlx_fill_image_color(&game->data, stripe, i, get_pixel(&game->sprites.north, texture_x, texture_y));
		i += 1;
	}
	while (i < HEIGHT)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.floor));
		i += 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:28:21 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/21 22:10:17 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*TODO: (talvez seja demais), verificar se todas as imagens tem o mesmo tamanho pois estamos a usar uma Macro para a width e height*/

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

	pixels = (int *)img->addr;
    return (pixels[y * TEXTURE_WIDTH + x]);
}

void	draw_stripe(t_game *game, t_draw draw_prop, size_t stripe, size_t texture_x, t_data *texture)
{
	size_t	i;
	size_t	texture_y;

	i = 0;
	while (i < draw_prop.start)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.ceil));
		i += 1;
	}
	/*Draw start until draw end is where we do the drawing of the textures*/
	while (i < draw_prop.end)
	{
		texture_y = ((double)i - draw_prop.start) / draw_prop.line_height * TEXTURE_HEIGHT;
		mlx_fill_image_color(&game->data, stripe, i, get_pixel(texture, texture_x, texture_y));
		i += 1;
	}
	while (i < HEIGHT)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.floor));
		i += 1;
	}
}

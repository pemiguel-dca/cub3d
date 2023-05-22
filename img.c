/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:28:21 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/22 15:22:04 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"

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

void	draw_stripe(t_game *game, t_draw draw_prop, size_t stripe, t_texture *texture)
{
	size_t	i;

	i = 0;
	while (i < draw_prop.start)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.ceil));
		i += 1;
	}
	while (i < draw_prop.end)
	{
		texture->y = ((double)i - draw_prop.start) / draw_prop.line_height * TEXTURE_HEIGHT;
		mlx_fill_image_color(&game->data, stripe, i, get_texture_pixel(texture));
		i += 1;
	}
	while (i < HEIGHT)
	{
		mlx_fill_image_color(&game->data, stripe, i, get_color(game->colors.floor));
		i += 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:28:21 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/19 16:34:28 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WHITE 0xFFFAFA
#define BLACK 0x000000
#define YELLOW 0xFFFF00

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

void	draw_4x4(t_game *game, int x, int y, int color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_fill_image_color(&game->data, (x * 4 + i), (y * 4 + j), color);
			j += 1;
		}
		i += 1;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_4x4(game, x, y, WHITE);
			else
				draw_4x4(game, x, y, YELLOW);
			x += 1;
		}
		y += 1;
	}
}

void	draw_vertical_line(t_game *game, t_draw *draw_prop, int stripe)
{
	size_t	i;

	i = 0;
	while (i < draw_prop->draw_start)
	{
		mlx_fill_image_color(&game->data, stripe, i, WHITE);
		i += 1;
	}
	while (i < draw_prop->draw_end)
	{
		mlx_fill_image_color(&game->data, stripe, i, BLACK);
		i += 1;
	}
	while (i < HEIGHT)
	{
		mlx_fill_image_color(&game->data, stripe, i, WHITE);
		i += 1;
	}
}

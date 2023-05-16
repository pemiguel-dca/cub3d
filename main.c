/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/16 20:20:48 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__debug_map(const t_game *game)
{
	printf("\nMAP\n");
	if (!game->map)
		return ;
	for (int i = 0; game->map[i]; ++i)
	{
		printf("%s\n", game->map[i]);
	}
}

void	__debug_identifiers(const t_game *game)
{
	printf("IDENTIFIERS\n");
	for (int i = 0; i < N_SETTINGS; ++i)
		printf("%s\n", game->settings[i]);
}

void start_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_NAME);
}

inline static void	mlx_fill_image_color(t_data *data, int w, int h, int color)
{
	ft_memset(data->addr, color, h * data->line_length + w * (data->bits_per_pixel / 8));
}

int	main(int argc, char **argv)
{
	char	**buffer;
	size_t	buf_len;
	t_game	game;
	int		fd;

	if (argc != 2 || !has_extension(argv[1]))
	{
		printf("Syntax: ./cub3d <*.cub>\n");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file '%s'\n", argv[1]);
		return (EXIT_FAILURE);
	}
	buffer = get_buffer(fd);
	buf_len = 0;
	while (buffer[buf_len])
		buf_len += 1;
	if (buf_len < 7) {
		printf("Invalid map\n");
		return (EXIT_FAILURE);
	}
	game = generate_game(buffer);
	__debug_identifiers(&game);
	__debug_map(&game);
	if (!is_valid_map(&game))
	{
		printf("Invalid map\n");
		free_game(&game);
		close(fd);
		return (EXIT_FAILURE);
	}

	start_window(&game);

	t_data	img;

	img.img = mlx_new_image(game.mlx, 960, 540);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// TODO create image from color and present it, after this start raycasting shit
	// also we'll need multiple images on the final game, no sense in having any image fields in t_game
	mlx_fill_image_color(&img, 960, 540, 0x00FF0000);
	mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);

	mlx_key_hook(game.win, &keys_pressed, &game);
	mlx_hook(game.win, 17, 0, &top_right, &game);
	mlx_loop(game.mlx);

	free_2Darrays(buffer);
	free_game(&game);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/17 20:13:52 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__debug_map(const t_game *game)
{
	printf("\nMAP\n");
	if (!game->map)
		return ;
	for (int i = 0; game->map[i]; ++i)
		printf("%s\n", game->map[i]);
	printf("Player's cardinal direction: %c\n", game->cardinal_direction);
}

void start_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_NAME);
}

/*
inline static void	mlx_fill_image_color(t_data *data, int w, int h, int color)
{
	ft_memset(data->addr, color, h * data->line_length + w * (data->bits_per_pixel / 8));
}
*/

int	main(int argc, char **argv)
{
	char	**buffer;
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
	if (!good_buffer((const char **)buffer))
	{
		free_2Darrays(buffer);
		close(fd);
		return (EXIT_FAILURE);
	}
	game = generate_game(buffer);
	// TODO refactor validation of reading and parsing file identifiers
	if (!is_valid_map(&game))
	{
		free_game(&game);
		close(fd);
		return (EXIT_FAILURE);
	}
	__debug_map(&game);

	start_window(&game);

	// TODO create image from color and present it, after this start raycasting shit
	// also we'll need multiple images on the final game, no sense in having any image fields in t_game
	// mlx_fill_image_color(&img, WIDTH, HEIGHT, 0x00FF0000);
	// mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);

	mlx_key_hook(game.win, &keys_pressed, &game);
	mlx_hook(game.win, 17, 0, &top_right, &game);
	mlx_loop(game.mlx);

	free_2Darrays(buffer);
	free_game(&game);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/18 17:46:35 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"

void	__debug_map(const char **map)
{
	for (int i = 0; map[i]; i += 1)
		printf("%s\n", map[i]);
}

void	__debug_scene(char **buffer)
{
	int i;

	for (i = 0; i < N_SETTINGS; i += 1)
		printf("%s\n", buffer[i]);
	printf("\n");
	__debug_map(buffer + i);
}

void	start_window(t_game *game)
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
	int		fd;
	char	**buffer;
	t_game	game;

	fd = open(argv[1], O_RDONLY);
	if (!valid_args(fd, argc, argv[1]))
		return (EXIT_FAILURE);
	buffer = get_buffer(fd);
	if (!valid_buffer((const char **)buffer)
		|| !valid_scene(buffer))
	{
		free_2Darrays(buffer);
		close(fd);
		return (EXIT_FAILURE);
	}
	// TODO refactor validation of reading and parsing file identifiers
	__debug_scene(buffer);
	game = generate_game(buffer);
	printf("Player's cardinal direction: %c\n", game.cardinal_direction);
	// TODO create image from color and present it, after this start raycasting shit
	// also we'll need multiple images on the final game, no sense in having any image fields in t_game
	// mlx_fill_image_color(&img, WIDTH, HEIGHT, 0x00FF0000);

	start(&game);

	mlx_key_hook(game.win, &keys_pressed, &game);
	mlx_hook(game.win, 17, 0, &top_right, &game);
	mlx_loop(game.mlx);

	free_game(&game);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/15 21:29:25 by pemiguel         ###   ########.fr       */
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

int	start_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_NAME);
	if (!game->mlx || !game->win)
	{
		printf("Error creating the window");
		return (EXIT_FAILURE);
	}
	game->img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img_data = mlx_get_data_addr(game->img_ptr, &game->bpp, &game->size_line, &game->endian);
	return (EXIT_SUCCESS);
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
	mlx_key_hook(game.win, &keys_pressed, &game);
	mlx_hook(game.win, 17, 0, &top_right, &game);
	mlx_loop(game.mlx);
	free_2Darrays(buffer);
	free_game(&game);
	close(fd);
}
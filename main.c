/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/24 13:05:05 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "player.h"

void	start_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_NAME);
}

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
		free_darrays(buffer);
		close(fd);
		return (EXIT_FAILURE);
	}
	game = generate_game(buffer);
	init_player(&game);
	start(&game);
	mlx_hook(game.win, 02, 1L << 0, keys_pressed, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	close(fd);
}

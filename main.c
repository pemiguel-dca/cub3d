/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:05:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/05/09 21:16:18 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	start_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_NAME);
	if (!game->mlx || !game->win)
	{
		printf("Error creating the window");
		return (EXIT_FAILURE);		
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
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
	game = generate_game(fd);

	for (int i = 0; i < game.cols; ++i)
	{
		for (int j = 0; j < game.rows; ++j)
		{
			printf("%c", game.buffer[i][j]);
		}
		printf("\n");
	}

	if (!is_valid_map(&game))
	{
		printf("Invalid map\n");
		free_game(&game);
		close(fd);
		return (EXIT_FAILURE);
	}
	start_window(&game);
	
	free_game(&game);
	close(fd);
}

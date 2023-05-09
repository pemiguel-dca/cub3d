#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "cub3d.h"
#include "mlx.h"

#define EXTENSION "cub"

static void	start_window(t_game *game)
{
	game->mlx = mlx_init();
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

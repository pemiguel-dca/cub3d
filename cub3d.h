#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
#include "mlx/mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ACCEPTABLE_CHARS "01NSEW"
#define EXTENSION "cub"
#define WIDTH 800
#define HEIGHT 600
#define WIN_NAME "cub3D"

/*KEY CODES*/

#define ESC 65307
#define LEFT_ARROW 65361
#define RIGTH_ARROW 65363
#define W 119
#define A 97
#define S 115
#define D 100

typedef struct {
	unsigned int	rows;
	unsigned int	cols;
	char			**buffer;
	void			*mlx;
	void			*win;
	int				bpp;
	int				size_line;
	int				endian;
	void			*img_ptr;
	char			*img_data;
}	t_game;

t_game	generate_game(int fd);
void	free_game(t_game *game);
bool	is_valid_map(t_game *game);

static inline bool	has_extension(const char *path)
{
	char	*sub;

	sub = ft_strrchr(path, '.');
	if (!sub || ft_strlen(sub + 1) != sizeof(EXTENSION) - 1
		|| ft_strncmp(sub + 1, EXTENSION, sizeof(EXTENSION) - 1))
		return (false);
	return (true);
}

/*close_game.c*/
int	close_window(int key, t_game *game);

/*parse_map.c*/
void	parse_map(t_game *game);
#endif // CUB3D_H

#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
#include "mlx.h"
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

typedef struct {
	unsigned int	rows;
	unsigned int	cols;
	char			**buffer;
	void			*mlx;
	void			*win;
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

#endif // CUB3D_H

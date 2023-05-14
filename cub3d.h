#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "validate.h"

# define ACCEPTABLE_CHARS "01NSEW "
# define EXTENSION "cub"
# define WIDTH 800
# define HEIGHT 600
# define WIN_NAME "cub3D"
# define N_TYPES 6

/*KEY CODES*/

# define ESC 65307
# define LEFT_ARROW 65361
# define RIGTH_ARROW 65363
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct
{
	unsigned int	cols;
	char			**buffer;
	char			**identifiers;
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

/*walls.c*/

static inline int	get_first_occur_row(t_game *game, size_t row)
{
	size_t	i;

	i = 0;
	while (game->buffer[row][i] && ft_isspace(game->buffer[row][i]))
		i += 1;
	return (i);
}
bool	surrounded_by_walls(const t_game *game);

/*validate.c*/

bool	is_valid_map(t_game *game);

static inline bool	verify_char(char to_verify)
{
	size_t	i;

	i = 0;
	while (ACCEPTABLE_CHARS[i])
	{
		if (to_verify == ACCEPTABLE_CHARS[i])
			return (true);
		i += 1;
	}
	return (false);
}

static inline bool is_cardinal_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

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

/*validate_identifiers*/

bool	validate_identifiers(t_game *game);

static inline void	free_2Darrays(char **stuff)
{
	size_t	i;

	i = 0;
	while (stuff[i])
	{
		free(stuff[i]);
		i += 1;
	}
	free(stuff);
}

#endif // CUB3D_H

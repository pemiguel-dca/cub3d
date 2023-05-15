#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "map_validation/validate.h"
# include "raycaster.h"

# define ACCEPTABLE_CHARS "01NSEW "
# define EXTENSION "cub"
# define WIDTH 800
# define HEIGHT 600
# define WIN_NAME "cub3D"
# define N_SETTINGS 6

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
	char			**map;
	char			**settings;
	void			*mlx;
	void			*win;
	int				bpp;
	int				size_line;
	int				endian;
	void			*img_ptr;
	char			*img_data;
	t_raycaster		*rc;
}	t_game;

char		**get_buffer(int fd);
t_game		generate_game(char **buffer);
t_vector	player_pos(const char **map);
void		free_game(t_game *game);

/*walls.c*/

static inline int	get_first_occur_row(const t_game *game, size_t row)
{
	size_t	i;

	i = 0;
	while (game->map[row][i] && ft_isspace(game->map[row][i]))
		i += 1;
	return (i);
}

bool	surrounded_by_walls(const t_game *game);

/*validate.c*/

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

bool	is_valid_map(t_game *game);

/*mlx_keys.c*/

int	top_right(t_game *game);
int	keys_pressed(int key, t_game *game);

/*validate_identifiers*/

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

bool	validate_identifiers(t_game *game);

#endif // CUB3D_H

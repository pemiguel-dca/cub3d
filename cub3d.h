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
# include "error_msg.h"

# define ACCEPTABLE_CHARS "01NSEW "
# define EXTENSION "cub"
# define WIDTH 960
# define HEIGHT 540
# define WIN_NAME "cub3D"
# define N_SETTINGS 6
# define N_CARDINAL_DIRECTIONS 4

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
	char	direction[3];
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct
{
	void	*north;
	void	*east;
	void	*south;
	void	*west;
}	t_sprites;

typedef struct
{
	t_color	ceil;
	t_color	floor;
}	t_colors;

typedef struct
{
	t_sprites	sprites;
	char		**map;
	t_colors	colors;
	char		cardinal_direction;
	void		*mlx;
	void		*win;
}	t_game;

char		**get_buffer(int fd);
t_game		generate_game(char **buffer);
void		free_game(t_game *game);

/*walls.c*/

static inline size_t	get_cols(const char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i += 1;
	return (i);
}

static inline size_t	get_first_occur_row(const t_game *game, size_t row)
{
	size_t	i;

	i = 0;
	while (game->map[row][i] && ft_isspace(game->map[row][i]))
		i += 1;
	return (i);
}

static inline size_t	get_last_occur_row(const t_game *game, size_t row)
{
	size_t	i;

	i = ft_strlen(game->map[row]) - 1;
	while (game->map[row][i] && ft_isspace(game->map[row][i]))
		i -= 1;
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

static inline t_vector	player_pos(const char **buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (buffer[i][j])
		{
			if (is_cardinal_direction(buffer[i][j]))
				break ;
			j += 1;
		}
		i += 1;
	}
	return ((t_vector){.x = j, .y = i});
}

static inline bool	has_extension(const char *path)
{
	char	*sub;

	sub = ft_strrchr(path, '.');
	return (sub && ft_strlen(sub + 1) == sizeof(EXTENSION) - 1
		&& !ft_strncmp(sub + 1, EXTENSION, sizeof(EXTENSION) - 1));
}

bool	is_valid_map(t_game *game);

/*mlx_keys.c*/

int	top_right(t_game *game);
int	keys_pressed(int key, t_game *game);

/*validate_settings*/

static inline void	free_2Darrays(char **stuff)
{
	size_t	i;

	if (!stuff)
		return ;
	i = 0;
	while (stuff[i])
	{
		free(stuff[i]);
		i += 1;
	}
	free(stuff);
}

bool	validate_settings(t_game *game);

/*open_textures.c*/

#endif // CUB3D_H

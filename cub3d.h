#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define ACCEPTABLE_CHARS "01NSEW"
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
bool	is_valid_map(t_game *game);

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

/*parse_map.c*/
void	parse_map(t_game *game);

/*validate_identifiers*/
bool	validate_identifiers(t_game *game);


static inline bool validate_len_types(const char **identifiers)
{
	size_t	i;

	i = 0;
	while (identifiers[i])
	{
		if (ft_strlen(identifiers[i]) > 2)
			return (false);
		i += 1;
	}
	return (true);
}

static inline bool validate_types(const char **identifiers)
{
	return ((validate_len_types(identifiers))
			&& (ft_strncmp(identifiers[0], "NO", 2) == 0 || (ft_strncmp(identifiers[0], "N", 1) == 0) && ft_strlen(identifiers[0]) == 1)
			&& (ft_strncmp(identifiers[1], "SO", 2) == 0 || (ft_strncmp(identifiers[1], "S", 1) == 0) && ft_strlen(identifiers[1]) == 1)
			&& (ft_strncmp(identifiers[2], "WE", 2) == 0 || (ft_strncmp(identifiers[2], "WE", 1) == 0) && ft_strlen(identifiers[2]) == 1)
			&& (ft_strncmp(identifiers[3], "EA", 2) == 0 || (ft_strncmp(identifiers[3], "EA", 1) == 0) && ft_strlen(identifiers[3]) == 1)
			&& (ft_strcmp(identifiers[4], "F") == 0)
			&& (ft_strcmp(identifiers[5], "C") == 0));
}


#endif // CUB3D_H

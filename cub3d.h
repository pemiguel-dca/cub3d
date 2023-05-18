#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "scene_validation/validate.h"
# include "raycaster.h"
# include "error_msg.h"

# define WIDTH 960
# define HEIGHT 540
# define WIN_NAME "cub3D"

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

/*generate_buffer.c*/

char	**get_buffer(int fd);

/*generate_game.c*/
void	start_window(t_game *game);

t_game	generate_game(char **buffer);

static inline bool	is_color(char c)
{
	return (c == 'F' || c == 'C');
}

/*mlx_keys.c*/

int		top_right(t_game *game);
int		keys_pressed(int key, t_game *game);

/*destroy.c*/

void	free_2Darrays(char **stuff);
void	free_game(t_game *game);

#endif // CUB3D_H

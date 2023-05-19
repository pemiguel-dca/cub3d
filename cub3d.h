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
# include "error_msg.h"

# define WIDTH 960
# define HEIGHT 540
# define WIN_NAME "cub3D"

# define TEXTURE_WIDTH 	64
# define TEXTURE_HEIGHT 64

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
	t_data		data;
}	t_game;

/*add this to raycaster.h in the end*/

typedef struct
{
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw;


static inline bool is_cardinal_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

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

/*img.c*/

void	mlx_fill_image_color(t_data *data, int w, int h, int color);
t_data	create_new_image(void *mlx);
void	draw(t_game *game, int x, int y, int color);
void	draw_vertical_line(t_game *game, t_draw draw_prop, int stripe);
void	draw_minimap(t_game *game);
#endif // CUB3D_H

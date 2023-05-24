SRCS=main.c destroy.c mlx_keys.c move.c rotate.c \
		generate_buffer.c generate_game.c \
		scene_validation/validate_settings.c scene_validation/validate.c scene_validation/validate_map.c scene_validation/map_info.c\
		raycaster.c img.c player.c texture.c


CFLAGS=-Wall -Wextra -Werror -fsanitize=leak
OBJS=$(SRCS:.c=.o)

CC=cc
MLX_FLAGS=-L mlx -lmlx -Ilmlx -lXext -lX11 -lbsd -lm
RM=rm -f
LIBFT=libft/libft.a
NAME=cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

run: re
	./$(NAME) map.cub
	@$(MAKE) clean -s

re: fclean all


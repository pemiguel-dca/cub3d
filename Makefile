SRCS=main.c game.c validate.c close_game.c parse_map.c validate_identifiers.c
OBJS=$(SRCS:.c=.o)

CC=cc
C_FLAGS=-Wall -Wextra -Werror -fsanitize=leak
MLX_FLAGS=-L mlx -lmlx -Ilmlx -lXext -lX11 -lbsd
RM=rm -f

LIBFT=libft/libft.a
NAME=cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C mlx
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

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


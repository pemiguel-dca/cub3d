SRCS=main.c game.c validate.c
OBJS=$(SRCS:.c=.o)

CC=cc
C_FLAGS=-Wall -Wextra -Werror -fsanitize=leak
MLX_FLAGS=-L ./mlx -lmlx -Ilmlx -lXext -lX11
RM=rm -f

LIBFT=libft/libft.a
NAME=cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

run: all clean
	./$(NAME) map.cub

re: fclean all

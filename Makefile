NAME = cub3d


LIB = ./MLX42/build
LIBA = libmlx42.a
LIBFT = libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRC =

OBJ = $(SRC:.c=.o)

all: setup $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft -I/usr/include -Imlx_linux -IMLX42/include/MLX42 -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB) $(LIBFT)/$(LIBFA) -L/usr/MLX42 -lmlx42 -ldl -lglfw -lm -lpthread -o $(NAME)


$(LIBFT)/$(LIBFA):
	@$(MAKE) -C $(LIBFT)

$(LIBFT)/%.o: $(LIBFT)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

debug: $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) -L$(LIBFT) $(RFLAG) $(OBJ) -ldl -lft -g3 -fsanitize=address -o $(NAME)

clean:
	make -C $(LIB) clean
	make -C $(LIBFT) clean
	$(RM) $(OBJ)


fclean: clean
	make -C $(LIBFT) fclean
	$(RM) $(NAME)
re: fclean all

setup:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	cd MLX42 && cmake -B build
	cmake --build MLX42/build -j4



.PHONY: all clean fclean re

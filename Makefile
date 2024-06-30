NAME = cub3d


LIB = ./MLX42/build
LIBA = libmlx42.a
LIBFT = libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

MAIN = cub3d
#MAIN = main
UTILS = map_valid map_prep map_init map_checks wall_check clean_up mini_map map_interpret

#SRC = $(addsuffix .c, $(MAIN))
SRC = $(addprefix srcs/, $(addsuffix .c, $(MAIN))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \

OBJ = $(SRC:.c=.o)

all: setup $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I$(LIBFT) -I/usr/include -Imlx_linux -I$(LIB)/include/MLX42 -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -lm -lpthread -o $(NAME)

$(LIBFT)/$(LIBFA):
	$(MAKE) -C $(LIBFT)

debug: $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -ldl -lmlx42 -g3 -fsanitize=address -o $(NAME)

clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(LIBFT) clean
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

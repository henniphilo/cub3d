NAME = cub3d


LIB = ./MLX42/build
LIBA = libmlx42.a
LIBFT = libft
LIBFA = libft.a


CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# MAIN = cub3d
MAIN = main check_params hooks movements keys
UTILS = mini_map_helper sprites_init bubbles map_valid map_prep map_init \
	map_checks wall_check clean_up map_interpret color_init pixel \
	sprite_utils 
INITS = init_camera init_texpaths init_map_data init_player init_ray \
	init_raycast init_render init_visuals 
RENDER = dda draw messages mini_map world_surfaces sprites \
	world_surfaces_helper
GAME_OBJECTS = player player_helper air doors targets 

SRC = $(addprefix srcs/, $(addsuffix .c, $(MAIN))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix srcs/inits/, $(INITS))) \
			$(addsuffix .c, $(addprefix srcs/render/, $(RENDER))) \
			$(addsuffix .c, $(addprefix srcs/game_objects/, $(GAME_OBJECTS))) \

OBJ_DIR = obj
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

all: setup $(OBJ_DIR) $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -Iinclude -I$(LIBFT) -I/usr/include -Imlx_linux -I$(LIB)/include/MLX42 -O3 -c $< -o $@
$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -I$(LIBFT) -I/usr/include -Imlx_linux -I$(LIB)/include/MLX42 -c $< -o $@

$(NAME): $(OBJ) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -lm -lpthread -o $(NAME)

$(LIBFT)/$(LIBFA):
	$(MAKE) -C $(LIBFT)

# Create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

debug: $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -ldl -lmlx42 -g3 -fsanitize=address -o $(NAME)

clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(LIBFT) clean
	$(RM) -r $(OBJ_DIR)

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

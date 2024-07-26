NAME = cub3d

LIB = ./MLX42/build
LIBA = libmlx42.a
LIBFT = libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined
RM = rm -f

MAIN = main check_params hooks movements keys
UTILS = mini_map_helper map_valid map_prep map_init \
	map_checks wall_check wall_check_helper clean_up map_interpret color_init pixel \
	free_arrays
INITS = init_camera init_texpaths init_map_data init_player init_ray \
	init_raycast init_render init_visuals
RENDER = dda draw messages mini_map world_surfaces sprites \
	world_surfaces_helper
GAME_OBJECTS = player player_helper
BONUS = bonus_main sprites_init sprite_utils air doors targets bubbles \
	clean_up_bonus dda_bonus free_arrays_bonus init_render_bonus init_visuals_bonus \
	map_init_bonus map_interpret_bonus mini_map_bonus movements_bonus sprite_utils_bonus \
	world_surfaces_helper_bonus check_params hooks keys_bonus mini_map_helper map_valid map_prep \
	map_checks wall_check wall_check_helper color_init pixel

SRC = $(addprefix srcs/, $(addsuffix .c, $(MAIN))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix srcs/inits/, $(INITS))) \
			$(addsuffix .c, $(addprefix srcs/render/, $(RENDER))) \
			$(addsuffix .c, $(addprefix srcs/game_objects/, $(GAME_OBJECTS))) \

OBJ_DIR = obj
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)

all: setup $(OBJ_DIR) $(NAME)

# Compiling .o files
$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -Iinclude -I$(LIBFT) -I/usr/include -Imlx_linux -I$(LIB)/include/MLX42 -c $< -o $@

# Linking the executable
$(NAME): $(OBJ) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(OBJ) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -lm -lpthread -o $(NAME)

# Ensure libft is built
$(LIBFT)/$(LIBFA):
	$(MAKE) -C $(LIBFT)

# Create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Debug build
debug: $(OBJ) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(OBJ) -L$(LIBFT) -lft -ldl -lmlx42 -g3 -o $(NAME)

clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(LIBFT) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

# Setup MLX42 library
setup:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	cd MLX42 && cmake -B build
	cmake --build MLX42/build -j4

.PHONY: all clean fclean re

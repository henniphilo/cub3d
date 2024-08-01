NAME = cub3d
NAME_BONUS = cub3d_bonus

LIB = ./MLX42/build
LIBA = libmlx42.a
LIBFT = ./libft
LIBFA = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
RM = rm -f

MAIN = main check_params hooks movements keys
BONUS_MAIN = bonus_main check_params_bonus
MANDATORY = init_render init_visuals dda mini_map world_surfaces_helper clean_up map_interpret map_init wall_check free_arrays

UTILS = mini_map_helper map_valid map_prep \
	map_checks  wall_check_helper color_init pixel \

INITS = init_camera init_texpaths init_map_data init_player init_ray \
	init_raycast
RENDER = draw world_surfaces \

GAME_OBJECTS = player player_helper
BONUS = sprites_init sprite_utils_bonus air doors targets bubbles sprites \
	clean_up_bonus dda_bonus free_arrays_bonus init_render_bonus init_visuals_bonus \
	map_init_bonus map_interpret_bonus mini_map_bonus movements_bonus \
	world_surfaces_helper_bonus keys_bonus messages hooks_bonus wall_check_bonus \

SRC = $(addprefix srcs/, $(addsuffix .c, $(MAIN))) \
			$(addsuffix .c, $(addprefix srcs/mandatory/, $(MANDATORY))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix srcs/inits/, $(INITS))) \
			$(addsuffix .c, $(addprefix srcs/render/, $(RENDER))) \
			$(addsuffix .c, $(addprefix srcs/game_objects/, $(GAME_OBJECTS))) \

SRC_BONUS = $(addprefix srcs/, $(addsuffix .c, $(BONUS_MAIN))) \
			$(addsuffix .c, $(addprefix srcs/bonus/, $(BONUS))) \
			$(addsuffix .c, $(addprefix srcs/game_objects/, $(GAME_OBJECTS))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
			$(addsuffix .c, $(addprefix srcs/inits/, $(INITS))) \
			$(addsuffix .c, $(addprefix srcs/render/, $(RENDER))) \

OBJ_DIR = obj
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:srcs/%.c=$(OBJ_DIR)/%.o)

all: setup $(OBJ_DIR) $(NAME)

bonus: setup $(OBJ_DIR) $(NAME_BONUS)

# Compiling .o files
$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -Iinclude -I$(LIBFT) -I/usr/include -Imlx_linux -I$(LIB)/include/MLX42 -c $< -o $@

# Linking the executable
$(NAME): $(OBJ) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -L/opt/homebrew/lib -lglfw -lm -lpthread -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS) $(LIB)/$(LIBA) $(LIBFT)/$(LIBFA)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_BONUS) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -L/opt/homebrew/lib -lglfw -lm -lpthread -o $(NAME_BONUS)

# Ensure libft is built
$(LIBFT)/$(LIBFA):
	$(MAKE) -C $(LIBFT)

# Create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

BONUS: $(NAME) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(OBJ_BONUS) -L$(LIB) -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -lm -lpthread -o $(NAME)

clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(LIBFT) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

# Setup MLX42 library
setup:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	cd MLX42 && cmake -B build
	cmake --build MLX42/build -j4

.PHONY: all clean fclean re

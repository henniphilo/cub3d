#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
//# include "MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include <errno.h> // perror, strerror
# include <math.h>
# include <stddef.h> // Null
# include <stdio.h>  // printf
# include <stdlib.h> // malloc, free, exit
# include <stdlib.h> // getenv
# include <string.h>
# include <unistd.h> // write, access, fork, execve, dup2, pipe, etc.

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 600
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define TILE_SIZE 64
# define SSIZE 15

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.05

/* Constants */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.05

/* Map Parsing */
int			check_file_ending_cub(char *file);
int			walls_check(t_game *game);
int			map_input_check(t_game *game);
int			get_map_start(t_game *game);
char		*get_from_cub(char *line, const char *direction);

void		which_color(t_game *game);
void		cub_input(t_game *game);
void		open_map(t_game *game, char *file);
void		space_cub(t_game *game, int fd);
void		get_cub(t_game *game, int fd);
void		space_map(t_game *game, int map_start);
void		init_map(t_game *game, int map_start);
void		actual_map(t_game *game);
void		print_map(t_game *game);
void		free_data(t_game *game);
void		free_cub(t_game *game);
void		get_textures(t_game *game);
void		get_img(t_game *game);
void		clean_texture(t_game *game);
void		clean_img(t_game *game);

/* Mini-Map*/
void		mm_get_img(t_game *game);
void		mm_get_textures(t_game *game);
void		draw_mini_map(t_game *game, int x, int y);
void		mini_map_init(t_game *game);

/* Hooks */
void		key_hook(mlx_key_data_t keydata, void *param);
void		loop_hook(void *param);

/* Initialize structs */
t_map		*init_map__(t_game *game, char *cub_file);
mlx_t		*init_mlx(t_game *game);
t_player	*init_player(t_game *game);
t_camera	*init_camera(t_game *game);

/* Rendering */
void		render_image(t_game *game);
void		setup_render_params(uint32_t x, t_render_data *render_data,
				mlx_image_t *image);

/* Cleanup */
int			terminate_game(t_game *game, int exit_code);

#endif

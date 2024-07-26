/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:31 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:56 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "structs.h"
# include <errno.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define TILE_SIZE 64
# define SSIZE 10

/* tex */
void			load_visuals(t_ressources *visual_res, t_texpaths *paths);

/* Map Parsing */
int				check_file_type(char *file);
int				walls_check(t_minimap *minimap);
int				check_adjacent(t_minimap *minimap);
int				get_map_start(unsigned int map_height, char **cub_input_table);
char			*get_path(char *line, const char *direction);
int				parse_input_table(t_game *game);
void			open_map(t_game *game, char *file);

void			parse_paths(int map_height, t_texpaths *paths,
					char **input_table);
int				init_input_table(t_minimap *minimap, char *file);
int				fill_input_table(t_minimap *minimap, char *file);
void			create_map(t_game *game);
void			free_data(t_game *game);
void			free_input_table(int map_height, char **input_table);
void			set_north(t_game *game);
void			set_south(t_game *game);
void			set_east(t_game *game);
void			set_west(t_game *game);

/* Mini-Map*/

void			draw_mini_map(t_game *game, mlx_image_t *img, int x, int y);
void			put_pixel_double(mlx_image_t *img, double x, double y,
					t_color color);
void			put_pixel(mlx_image_t *img, int x, int y, t_color color);
void			put_block(mlx_image_t *img, t_color color, int x, int y);
void			fill_half(t_game *game, t_color color, int start_y, int end_y);
void			add_look(t_game *game, mlx_image_t *img, int start_y,
					int end_y);
void			add_look(t_game *game, mlx_image_t *img, int start_y,
					int end_y);
void			render_mini_map(t_game *game);
void			put_block_double(mlx_image_t *img, t_color color, double x,
					double y);
char			get_direction(mlx_key_data_t key, char cur_direct);
int				get_color_int(const char *color_str);
int				get_color_value(const char *color_str, int *index);
t_color			int_to_color(int color);
t_game			*mini_map_init(t_game *game);
void			print_got_air(t_game *game);
void			init_look(t_game *game);

/* Hooks */
void			key_hook(mlx_key_data_t keydata, void *param);
void			loop_hook(void *param);
void			scroll_hook(double xdelta, double ydelta, void *param);
void			keys_rotate(mlx_key_data_t keydata, t_game *game);
void			keys_act(t_game *game, mlx_key_data_t keydata);
void			keys_walk(t_game *game, mlx_key_data_t keydata);

/* Initialize data */
t_game			*get_mlx(t_game *game);
void			init_sprites(t_game *game);
t_minimap		init_map_data(void);
void			init_data(t_game *game);
t_camera		init_camera(void);
t_texpaths		init_texpaths(void);
t_player		init_player(void);
t_ressources	init_visuals(void);
t_raycast		init_raycast(void);
t_ray			init_ray(void);
t_render		init_render_data(void);
t_game			*set_player(t_game *game);

/* Rendering */
void			render_surfaces(t_game *game);
void			setup_render_params(uint32_t x, t_render *render,
					mlx_image_t *image);
void			perform_dda(t_render *render, t_minimap *minimap);
void			draw_line(int x, t_game *game, mlx_image_t *image,
					mlx_texture_t *tex);
void			render_sprites(t_game *game);
void			render_ingame_messages(t_game *game);
void			render_logic(t_game *game, int x);

/* Cleanup */
void			free_string_arr(char **string_arr);
int				terminate_game(t_game *game, int exit_code);
void			free_paths(t_texpaths *paths);

/* Argument checks */
void			argv_check(int argc, char **argv);
int				check_game_param(t_game *game);
int				check_minimap(t_minimap *minimap);
int				check_render_data(t_render *render);
int				check_visual(t_ressources *vis);

/* Drawing utils */
uint32_t		get_pixel(mlx_texture_t *img, int x, int y);
void			set_pixel(mlx_image_t *img, int x, int y, uint32_t color);

/* Sprites */
void			open_doors(t_render *render, t_minimap *minimap);
void			close_doors(t_game *game, t_minimap *minimap);
int				is_door(t_render *render, int x, int y);
int				is_target(t_render *render, int x, int y);
void			get_target(t_game *game, t_minimap *minimap);
int				is_air(t_render *render, int x, int y);
void			get_air(t_game *game, t_minimap *minimap);
void			create_bubbles(t_game *game);
void			init_sprites_count(t_game *game);
void			set_textures(int sprite_count, t_sprite *sprites_arr,
					mlx_texture_t *texture, t_game *game);
void			set_position(int sprite_count, t_sprite *sprites_arr, char type,
					t_game *game);
void			init_bg_img(t_game *game);

/* Movements */
void			rotate(t_render *render, int direction);
void			move_straight(t_game *game, t_minimap *minimap,
					t_render *render, int direction);
void			move_sideways(t_game *game, t_minimap *minimap,
					t_render *render, int direction);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:27 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 17:32:30 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Constants */
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 800
//# define WINDOW_WIDTH 1920
//# define WINDOW_HEIGHT 1080
# define MOVE_SPEED 0.33
# define ROT_SPEED 0.05
# define DOOR_PATH "./img/algen.png"
# define TARGET_PATH "./img/fish500.png"
# define AIR_PATH "./img/Scuba_tank.png"
# define BUBBLE_PATH "./img/bubb800.png"
# define C_BLUE (t_color){0, 0, 155, 255}
# define C_SIDE (t_color){100, 0, 155, 255}
# define C_WALL (t_color){0, 0, 0, 255}
# define C_AIR (t_color){200,0,100,255}
# define C_TARGET (t_color){150, 150, 0, 255}
# define C_DOOR (t_color){100, 80, 150, 255}
# define C_FLOOR (t_color){255, 255, 255, 255}
# define C_PLAYER (t_color){0, 0, 255, 255}
# define C_TRANSPARENT (t_color){0, 0, 0, 0}

typedef struct s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_color;

typedef struct s_texpaths
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor;
	char			*ceiling;
	char			*door;
	char			*target;
	char			*bubbles;
	char			*air;
}					t_texpaths;

typedef struct s_visual
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*door;
	mlx_texture_t	*player;
	mlx_texture_t	*target;
	mlx_texture_t	*bubbles;
	mlx_image_t		*bubbles_img;
	mlx_texture_t	*air;

	mlx_image_t		*target_img;

	t_color			c_floor;
	t_color			c_ceiling;
}					t_visual;

typedef struct s_camera
{
	double			camerax;
	double			plane_x;
	double			plane_y;
}					t_camera;

typedef struct s_sprite
{
	double			pos_x;
	double			pos_y;
	double			dist_x;
	double			dist_y;
	double			inverse_determinate;
	double			transform_x;
	double			transform_y;
	int				tex_x;
	int				tex_y;
	int				screen_x;
	int				height;
	int				width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				active;
	mlx_image_t		*img;
}					t_sprite;

typedef struct s_raycast
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			perp_wall_dist;
	int				tex_x;
	double			tex_pos;
	double			tex_step_size;
}					t_raycast;

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				grid_pos_x;
	int				grid_pos_y;
	int				step_x;
	int				step_y;
}					t_ray;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}					t_player;

typedef struct s_render_data
{
	double			z_buffer[WINDOW_WIDTH];
	t_player		player;
	t_camera		camera;
	t_ray			ray;
	t_raycast		raycast;
	t_sprite		*targets;
	t_sprite		*doors;
	t_sprite		*oxygen_tanks;
	int				count_oxy;
	int				count_oxy_caught;
	int				count_fish_caught;
	int				count_door;
	int				count_target;
	int				flag_hit_wall;
	int				flag_hit_door;
	int				flag_hit_target;
	int				flag_hit_air;
	int				flag_side;
	int				flag_render;
	mlx_image_t		*screen_image;
	t_visual		*vis;
}					t_render_data;

typedef struct s_map_data
{
	char			**input_table;
	char			**map;
	int				height;
	int				width;
	int				y_axis;
	int				*x_axis;
	char			first_dir;
}					t_map_data;

typedef struct s_game
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	t_map_data		map_data;
	t_render_data	render_data;
	t_visual		visual_res;
	t_texpaths		texpaths;
}					t_game;

#endif

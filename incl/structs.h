#ifndef STRUCTS_H
# define STRUCTS_H

/* Constants */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.05

typedef struct s_sprite
{
	double			pos_x;
	double			pos_y;
	int				open_door;
	int				got_target;
	char			direction;
	mlx_image_t	*img;
	int				got_air;
	int				id;
}					t_sprite;

typedef struct s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_color;

typedef struct s_map_data
{
	char			**input_table;
	char			**map;
	int				height;
	int				width;
	int				y_axis;
	int				*x_axis;
	t_sprite		*player;
	char			first_dir;
}					t_map_data;

typedef struct s_texpaths
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*floor;
	char			*ceiling;
	char			*door;
	char			*target;
	char		*bubbles;
	char		*air;
}					t_texpaths;

typedef struct s_visual
{
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
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

// typedef struct s_image
// {
// 	mlx_image_t		*NO;
// 	mlx_image_t		*SO;
// 	mlx_image_t		*WE;
// 	mlx_image_t		*EA;
// 	mlx_image_t		*door;
// 	mlx_image_t		*player;
// 	mlx_image_t		*target;
// }					t_image;

typedef struct s_camera
{
	double			cameraX;
	double			plane_x;
	double			plane_y;
}					t_camera;

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
	double			prev_pos_x;
	double			prev_pos_y;
	double			dir_x;
	double			dir_y;
}					t_player;

typedef struct s_render_data
{
	t_player		player;
	t_camera		camera;
	t_ray			ray;
	t_raycast		raycast;
	t_sprite		*targets;
	t_sprite		*doors;
	double			z_buffer[WINDOW_WIDTH];
	t_sprite		*air_sprites;
	int				flag_hit_wall;
	int				flag_hit_door;
	int				flag_hit_target;
	int				flag_hit_air;
	int				flag_side;
}					t_render_data;

typedef struct s_game
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	t_map_data		map_data;
	t_render_data	render_data;
	t_visual		visual_res;
	t_texpaths		texpaths;
	int				air_count;
	int				door_count;
	int				target_count;
	int				air_caught;
}					t_game;

#endif

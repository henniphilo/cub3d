#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_sprite
{
	double			pos_x;
	double			pos_y;
	int				open_door;
	int				got_target;
	int				id;
}	t_sprite;


typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_map
{
	char			**cub;
	char			**map;
	int				height;
	int				width;
	int				y_axis;
	int				*x_axis;
//	t_sprite		player;
}					t_map;

typedef struct s_look
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*floor;
	char		*ceiling;
	char		*door;
	char		*target;
	char		*bubbles;
	char		*sand;
	char		first_dir;
}					t_look;

typedef struct s_textures
{
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
	mlx_texture_t	*door;
	mlx_texture_t	*player;
	mlx_texture_t	*target;
	mlx_texture_t	*bubbles;
	mlx_texture_t	*sand;
}					t_textures;


typedef struct s_image
{
	mlx_image_t	*bubbles;
	mlx_image_t	*sand;
	int			c_floor;
	int			c_ceiling;
}					t_image;

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
	t_sprite		*ta_sprites;
	t_sprite		*do_sprites;
	int				flag_hit;
	int				flag_hit_door;
	int				flag_hit_target;
	int				flag_side;
}					t_render_data;

typedef struct s_game
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	t_map			map;
	t_look			look;
	t_render_data	render_data;
	t_textures		tex;
	t_image			image;
	int				door_count;
	int				target_count;
}					t_game;

#endif

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_sprite
{
	double			pos_x;
	double			pos_y;
	char		direction;
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
	t_sprite		player;
}					t_map;

// kann dann in textures umgewandelt werden
typedef struct s_look
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*floor;
	char			*ceiling;
}					t_look;

typedef struct s_texture
{
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
	mlx_texture_t	*floor;
	mlx_texture_t	*ceiling;
	mlx_texture_t	*wall;
	mlx_texture_t	*player;
	mlx_texture_t	*target;
}	t_texture;

//image als untergrund der so gross ist wie unser window

typedef struct s_image
{
	mlx_image_t	*NO;
	mlx_image_t	*SO;
	mlx_image_t	*WE;
	mlx_image_t	*EA;
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*target;
	int			c_floor;
	int			c_ceiling;
}	t_image;

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
	int				flag_hit;
	int				flag_side;
}					t_render_data;

typedef struct s_game
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	t_map			map;
	t_look			look;
	t_render_data	render_data;
	t_texture		tex;
	t_image			image;
}					t_game;

#endif

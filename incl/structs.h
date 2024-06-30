#ifndef STRUCTS_H
# define STRUCTS_H

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 64
#define SSIZE 15

/* Constants */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MOVE_SPEED 0.5
#define ROT_SPEED 0.05

typedef struct s_sprite
{
	int			pos_x;
	int			pos_y;
}	t_sprite;

typedef struct s_map
{
	char		**cub;
	char		**map;
	int			height;
	int			width;
	int			y_axis;
	int			*x_axis;
	t_sprite	player;
}	t_map;

//kann dann in textures umgewandelt werden
typedef struct s_look
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*floor;
	char	*ceiling;
}	t_look;

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
}	t_image;

typedef struct s_game
{
	mlx_t		*mlx_ptr;
	t_map		map;
	t_look		look;
	t_scene		scene;
	t_texture	tex;
	t_image		img;
}	t_game;

typedef struct s_scene
{

	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
}	t_scene;

#endif

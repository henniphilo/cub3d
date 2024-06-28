#ifndef STRUCTS_H
# define STRUCTS_H

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 600
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 64
#define SSIZE 15

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;

}	t_map;

typedef struct s_texture
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
}	t_texture;

typedef struct s_game
{
	mlx_t		*mlx_ptr;
	t_map		map;
	t_texture	texture;
	t_scene	scene;
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

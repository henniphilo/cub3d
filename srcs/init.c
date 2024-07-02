#include "../incl/cub3d.h"

t_game	*init_mlx(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	if (!game)
	{
		ft_putendl_fd("Failed to initialize MLX42", STDERR_FILENO);
		return (NULL);
	}
	mlx = mlx_init((SSIZE * game->map.width), (SSIZE * game->map.height),
			"cub3d", true);
	if (!mlx)
	{
		ft_putendl_fd("Failed to initialize MLX42", STDERR_FILENO);
		return (NULL);
	}
	image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!image)
	{
		ft_putendl_fd("Failed to create image", STDERR_FILENO);
		return (NULL);
	}
	return (game);
}

t_map	*init_map__(t_game *game, char *cub_file)
{
	open_map(game, cub_file);
	if (!game->map.map)
		return (NULL);
	return (game->map.map);
}

t_player	*init_player(t_game *game)
{
	t_player	player;

	player = game->render_data.player;
	player.pos_x = game->map.player.pos_x;
	player.pos_y = game->map.player.pos_y;
	player.dir_x = -1.0;
		// TODO: translate NO SE WE EA into direction vector
	player.dir_y = 0.0;
	return (&player);
}

t_camera	*init_camera(t_game *game)
{
	t_camera camera;

	camera = game->render_data.camera;

	camera.plane_x = 0.0;
	camera.plane_y = 0.66;
	return (&camera);
}
#include "../incl/cub3d.h"

t_game	*init_mlx(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (!game)
	{
		ft_putendl_fd("Failed to initialize MLX42", STDERR_FILENO);
		return (NULL);
	}
	mlx = mlx_init((WINDOW_WIDTH), (WINDOW_HEIGHT),
			"cub3d", true);
	if (!mlx)
	{
		ft_putendl_fd("Failed to initialize MLX42", STDERR_FILENO);
		return (NULL);
	}
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img)
	{
		ft_putendl_fd("Failed to create image", STDERR_FILENO);
		return (NULL);
	}
	game->img = img;
	game->mlx_ptr = mlx;
	return (game);
}

t_game	*init_map__(t_game *game, char *cub_file)
{
	open_map(game, cub_file);

	if (!game->map.map)
		return (NULL);
	return (game);
}

t_game	*init_player(t_game *game)
{
	t_player	*player;

	player = &game->render_data.player;
	init_player_pos(game);
	player->prev_pos_x = player->pos_x;
	player->prev_pos_y = player->pos_y;
	init_player_direction(game);
	return (game);
}

void	init_player_direction(t_game *game)
{
	int		x;
	int		y;
	char	direction;
	t_render_data	*render_data;

	render_data = &game->render_data;
	y = 0;
	while (y < game->map.y_axis)
	{
		x = 0;
		while (x < game->map.x_axis[y])
		{
			direction = game->map.map[y][x];

			if (direction == 'N')
			{
				game->render_data.player.dir_x = 0.0;
				game->render_data.player.dir_y = -1.0;
				game->render_data.camera.plane_x = -0.66;
				game->render_data.camera.plane_y = 0;
				render_data->player.pos_x = x;
				render_data->player.pos_y = y;
				game->look.first_dir = direction;
			}
			else if (direction == 'E')
			{
				game->render_data.player.dir_x = 1.0;
				game->render_data.player.dir_y = 0.0;
				game->render_data.camera.plane_x = 0.;
				game->render_data.camera.plane_y = -0.66;
				render_data->player.pos_x = x;
				render_data->player.pos_y = y;
				game->look.first_dir = direction;
			}
			else if (direction == 'S')
			{
				game->render_data.player.dir_x = 0.0;
				game->render_data.player.dir_y = 1.0;
				game->render_data.camera.plane_x = 0.66;
				game->render_data.camera.plane_y = 0;
				render_data->player.pos_x = x;
				render_data->player.pos_y = y;
				game->look.first_dir = direction;
			}
			else if (direction == 'W')
			{
				game->render_data.player.dir_x = -1.0;
				game->render_data.player.dir_y = 0.0;
				game->render_data.camera.plane_x = 0;
				game->render_data.camera.plane_y = 0.66;
				render_data->player.pos_x = x;
				render_data->player.pos_y = y;
				game->look.first_dir = direction;
			}
			x++;
		}
		y++;
	}
	printf("first dir is %c\n", game->look.first_dir);
}

// t_game	*init_camera(t_game *game)
// {
// 	t_camera *camera;

// 	camera = &game->render_data.camera;

// 	if (game->map.player.direction == 'N')
// 	{
// 		camera->plane_x = 0.66;
// 		camera->plane_y = 0;
// 	}
// 	if (game->map.player.direction == 'W')
// 	{
// 		camera->plane_x = 0.0;
// 		camera->plane_y = -0.66;
// 	}
// 	if (game->map.player.direction == 'E')
// 	{
// 		camera->plane_x = 0.0;
// 		camera->plane_y = 0.66;
// 	}
// 	if (game->map.player.direction == 'S')
// 	{
// 		camera->plane_x = -0.66;
// 		camera->plane_y = 0.0;
// 	}
// 	return (game);
// }

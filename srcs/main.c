
#include "../incl/cub3d.h"

t_game	*get_mlx(t_game *game)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (!game)
	{
		ft_putendl_fd("Failed to initialize MLX42", STDERR_FILENO);
		return (NULL);
	}
	mlx = mlx_init((WINDOW_WIDTH), (WINDOW_HEIGHT),
			"cub3d", false);
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
void	init_data(t_game *game)
{
	game->render_data.count_target = 0;
	game->render_data.count_door = 0;
	game->render_data.count_oxy = 0;
	game->render_data.count_oxy_caught = 0;
	game->render_data.count_fish_caught = 0;
	game->img = NULL;
	game->mlx_ptr = NULL;
	game->map_data = init_map_data();
	game->render_data = init_render_data();
	game->visual_res = init_visuals();
}

int	main(int argc, char **argv)
{
	t_game	game;

		args_check(argc, argv);
	srand(time(NULL));
	init_data(&game);
	open_map(&game, argv[1]);
	set_player(&game);
	get_mlx(&game);
	init_sprites(&game);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_put_string(game.mlx_ptr, "Hurry! You need air!\n", 100, 0);
	mlx_key_hook(game.mlx_ptr, key_hook, &game);
	mlx_scroll_hook(game.mlx_ptr, scroll_hook, &game);
	mlx_loop(game.mlx_ptr);
	// free_data(&game);
	// clean_img(&game);
	// clean_texture(&game);
	return (EXIT_SUCCESS);
}

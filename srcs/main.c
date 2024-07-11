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
void	init_data(t_game *game)
{
	game->target_count = 0;
	game->door_count = 0;
	game->air_caught = 0;
	game->air_count = 0;
}


int	main(int argc, char **argv)
{
	t_game	game;

	args_check(argc, argv);
	srand(time(NULL));
	init_data(&game);
	if (!(init_map__(&game, argv[1]) && init_mlx(&game) && init_player(&game)))
		return (terminate_game(&game, EXIT_FAILURE));
	init_sprites(&game);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_key_hook(game.mlx_ptr, key_hook_, &game);
	mlx_scroll_hook(game.mlx_ptr, scroll_hook, &game);
	mlx_loop(game.mlx_ptr);
	clean_img(&game);
	mlx_delete_image(game.mlx_ptr, game.img);
	mlx_terminate(game.mlx_ptr);
	return (EXIT_SUCCESS);
}

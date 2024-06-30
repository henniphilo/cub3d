#include "../incl/cub3d.h"

static void	hook(void *ptr)
{
	t_game	*game;

	game = ptr;
	//transparent_minimap(game);
}

static void	game_init(t_game *game)
{
	game->mlx_ptr = mlx_init((SSIZE * game->map.width),
		(SSIZE * game->map.height), "cub3d", true);
	if (!(game->mlx_ptr))
	{
		printf ("mlx ptr error \n");
		exit (1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*file;

	if (argc == 2)
	{
		file = argv[1];
		open_map(&game, file);
		game_init(&game);
		mm_get_img(&game);
		mini_map_init(&game);
		mlx_loop_hook(game.mlx_ptr, &hook, &game);
		mlx_key_hook(game.mlx_ptr, &key_hook, &game);
		mlx_loop(game.mlx_ptr);
		//printf("hello cub3d :)\n");
		free_data(&game);
		clean_img(&game);
		mlx_terminate(game.mlx_ptr);
	}
	else
		printf("please select map \n");
	return (0);
}


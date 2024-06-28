#include "../incl/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	*file;

	if (argc == 2)
	{
		file = argv[1];
		open_map(&game, file);
		// game.mlx_ptr = mlx_init((SSIZE * game.map.width),
		// 	(SSIZE * game.map.height), "cub3d", false);
		// if (!(game.mlx_ptr))
		// {
		// 	printf ("mlx ptr error \n");
		// 	return (1);
		// }
		// printf("hello cub3d :)\n");
		free_data(&game);
	}
	else
		printf("please select map \n");
	return (0);
}


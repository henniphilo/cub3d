#include "../incl/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	args_check(argc, argv);
	if (!(init_map__(&game, argv[1]) && init_mlx(&game) && init_player(&game)))
		return (terminate_game(&game, EXIT_FAILURE));
	mlx_key_hook(game.mlx_ptr, key_hook_, &game);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_loop(game.mlx_ptr);
	mlx_delete_image(game.mlx_ptr, game.img);
	mlx_terminate(game.mlx_ptr);
	return (EXIT_SUCCESS);
}

// wenn a oder d lang genug gedrueckt einmal um die achse drehen?
// abstand nicht richtig berechnet muss
// geht nicht nach linksrechts muss auf directions beruhen

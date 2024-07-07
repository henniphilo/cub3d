#include "../incl/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	args_check(argc, argv);
	if (!(init_map__(&game, argv[1]) && init_mlx(&game) && init_player(&game)))
		return (terminate_game(&game, EXIT_FAILURE));
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_key_hook(game.mlx_ptr, key_hook_, &game);
	mlx_loop(game.mlx_ptr);
	//terminate_game(&game, 0);
	mlx_delete_image(game.mlx_ptr, game.img);
	mlx_terminate(game.mlx_ptr);
	return (EXIT_SUCCESS);
}

//minimap muss nach direction angepasst werden und sich dahin bewegen (tut es aber nicht smooth)
// muss noch minimap nach vorne holen
// klappt noch nicht mit mm im hook loop
// wenn  player pos init in render_data.player dann als pointer ubergeben buggt aber beim laufen in alle richtungen nicht wenn hard coded
// bilder spiegelverkehrt projiziert wenn nicht norden warum?

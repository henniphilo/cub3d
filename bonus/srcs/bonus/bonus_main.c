/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:32:21 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/26 11:39:11 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	argv_check(argc, argv);
	srand(time(NULL));
	init_data(&game);
	open_map(&game, argv[1]);
	set_player(&game);
	get_mlx(&game);
	init_sprites(&game);
	mlx_loop_hook(game.render.mlx_ptr, loop_hook, &game);
	mlx_put_string(game.render.mlx_ptr, "Hurry! You need air!\n", 100, 0);
	mlx_key_hook(game.render.mlx_ptr, key_hook, &game);
	mlx_scroll_hook(game.render.mlx_ptr, scroll_hook, &game);
	mlx_loop(game.render.mlx_ptr);
	free_data(&game);
	mlx_terminate(game.render.mlx_ptr);

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:20:07 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/23 15:52:54 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mlx = mlx_init((WINDOW_WIDTH), (WINDOW_HEIGHT), "cub3d", false);
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
	game->render.screen_image = img;
	game->render.mlx_ptr = mlx;
	return (game);
}

void	init_data(t_game *game)
{
	game->render = init_render_data();
	game->minimap = init_map_data();
}

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

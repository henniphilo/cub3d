/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:11:21 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 12:50:11 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	t_render	*render;
	t_minimap		*minimap;

	game = (t_game *)param;
	render = &game->render;
	minimap = &game->minimap;
	if (keydata.action == MLX_PRESS)
	{
		keys_act(game, keydata);
		render->flag_render = 1; // was ist das??? diese hier sehr gut
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		keys_rotate(keydata, render);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT
		|| keydata.action == MLX_RELEASE)
		keys_walk(game, keydata);
}

void	keys_walk(t_game *game, mlx_key_data_t keydata)
{
	t_render	*render;
	t_minimap		*minimap;

	render = &game->render;
	minimap = &game->minimap;
	if (keydata.key == MLX_KEY_W)
		move_straight(game, minimap, render, 1);
	if (keydata.key == MLX_KEY_S)
		move_straight(game, minimap, render, -1);
	if (keydata.key == MLX_KEY_A)
		move_sideways(game, minimap, render, 1);
	if (keydata.key == MLX_KEY_D)
		move_sideways(game, minimap, render, -1);
	if (game->render.count_oxy_caught != 0)
		create_bubbles(game);
}

void	keys_rotate(mlx_key_data_t keydata, t_render *render)
{
	if (keydata.key == MLX_KEY_LEFT)
		rotate(render, -1);
	if (keydata.key == MLX_KEY_RIGHT)
		rotate(render, 1);
}

void	keys_act(t_game *game, mlx_key_data_t keydata)
{
	t_render	*render;
	t_minimap		*minimap;

	render = &game->render;
	minimap = &game->minimap;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		free_data(game);
		mlx_close_window(game->mlx_ptr);
	}
	if (keydata.key == MLX_KEY_SPACE)
	{
		open_doors(render, minimap);
		ft_putendl_fd("SPACE", STDERR_FILENO);
	}
	if (keydata.key == MLX_KEY_X)
	{
		get_target(game, minimap);
		ft_putendl_fd("X", STDERR_FILENO);
	}
	if (keydata.key == MLX_KEY_Z)
	{
		get_air(game, minimap);
		ft_putendl_fd("Z", STDERR_FILENO);
	}
}

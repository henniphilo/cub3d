/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:11:21 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/26 13:28:42 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	t_render	*render;

	game = (t_game *)param;
	render = &game->render;
	if (keydata.action == MLX_PRESS)
	{
		keys_act(game, keydata);
		render->flag_render = 1;
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		keys_rotate(keydata, game);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT
		|| keydata.action == MLX_RELEASE)
		keys_walk(game, keydata);
}

void	keys_walk(t_game *game, mlx_key_data_t keydata)
{
	t_render	*render;
	t_minimap	*minimap;

	render = &game->render;
	minimap = &game->minimap;
	if (keydata.key == MLX_KEY_ESCAPE)
		return ;
	if (keydata.key == MLX_KEY_W)
		move_straight(game, minimap, render, 1);
	if (keydata.key == MLX_KEY_S)
		move_straight(game, minimap, render, -1);
	if (keydata.key == MLX_KEY_A)
		move_sideways(game, minimap, render, 1);
	if (keydata.key == MLX_KEY_D)
		move_sideways(game, minimap, render, -1);
}

void	keys_rotate(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		return ;
	if (keydata.key == MLX_KEY_LEFT)
		rotate(&game->render, -1);
	if (keydata.key == MLX_KEY_RIGHT)
		rotate(&game->render, 1);
}

void	keys_act(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->render.mlx_ptr);
	}
}

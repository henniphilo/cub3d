/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:53 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/19 12:50:08 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_game			*game;
	t_render	*render;

	(void)xdelta;
	game = (t_game *)param;
	render = &game->render;
	if (ydelta > 0)
		rotate(render, 1);
	else if (ydelta < 0)
		rotate(render, -1);
}

void	loop_hook(void *param)
{
	t_game	*game;
	int		render_flag;

	game = (t_game *)param;
	// if (check_game_param(game) == -1)
	// 	terminate_game(game, EXIT_FAILURE);
	render_flag = game->render.flag_render;
	if (render_flag)
	{
		render_ingame_messages(game);
		render_surfaces(game);
		render_sprites(game);
		render_mini_map(game);
		render_flag = 0;
	}
}

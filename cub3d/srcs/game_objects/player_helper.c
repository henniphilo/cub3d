/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:29:30 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/21 19:29:31 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	set_north(t_game *game)
{
	game->render.player.dir_x = 0.0;
	game->render.player.dir_y = -1.0;
	game->render.camera.plane_x = -0.66;
	game->render.camera.plane_y = 0;
}

void	set_south(t_game *game)
{
	game->render.player.dir_x = 0.0;
	game->render.player.dir_y = 1.0;
	game->render.camera.plane_x = 0.66;
	game->render.camera.plane_y = 0;
}

void	set_east(t_game *game)
{
	game->render.player.dir_x = 1.0;
	game->render.player.dir_y = 0.0;
	game->render.camera.plane_x = 0.;
	game->render.camera.plane_y = -0.66;
}

void	set_west(t_game *game)
{
	game->render.player.dir_x = -1.0;
	game->render.player.dir_y = 0.0;
	game->render.camera.plane_x = 0;
	game->render.camera.plane_y = 0.66;
}

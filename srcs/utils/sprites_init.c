/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:47 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/22 17:56:53 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	init_doors(t_game *game)
{
	game->render.doors = ft_calloc(game->render.door_count + 1,
			sizeof(t_sprite));
	if (!game->render.doors)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render.door_count, game->render.doors,
		game->render.res.door, game);
	set_position(game->render.door_count, game->render.doors, 'D',
		game);
}

void	init_targets(t_game *game)
{
	game->render.targets = ft_calloc(game->render.target_count + 1,
			sizeof(t_sprite));
	if (!game->render.targets)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render.target_count, game->render.targets,
		game->render.res.target, game);
	set_position(game->render.target_count, game->render.targets, 'T',
		game);
}

void	init_air(t_game *game)
{
	game->render.air = ft_calloc(game->render.air_count + 1,
			sizeof(t_sprite));
	if (!game->render.air)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render.air_count, game->render.air,
		game->render.res.air, game);
	set_position(game->render.air_count, game->render.air, 'L', game);
}

void	init_sprites(t_game *game)
{
	if (!game || check_minimap(&game->minimap))
		terminate_game(game, EXIT_FAILURE);
	init_sprites_count(game);
	init_doors(game);
	init_targets(game);
	init_air(game);
	init_look(game);
	init_bg_img(game);
}

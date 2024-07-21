/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:47 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 14:52:17 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	init_doors(t_game *game)
{
	game->render_data.doors = ft_calloc(game->render_data.door_count + 1,
			sizeof(t_sprite));
	if (!game->render_data.doors)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render_data.door_count, game->render_data.doors,
		game->render_data.visual_ressources->door, game);
	set_position(game->render_data.door_count, game->render_data.doors, 'D',
		game);
}

void	init_targets(t_game *game)
{
	game->render_data.targets = ft_calloc(game->render_data.target_count + 1,
			sizeof(t_sprite));
	if (!game->render_data.targets)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render_data.target_count, game->render_data.targets,
		game->render_data.visual_ressources->target, game);
	set_position(game->render_data.target_count, game->render_data.targets, 'T',
		game);
}

void	init_air(t_game *game)
{
	game->render_data.air = ft_calloc(game->render_data.air_count + 1,
			sizeof(t_sprite));
	if (!game->render_data.air)
		terminate_game(game, EXIT_FAILURE);
	set_textures(game->render_data.air_count, game->render_data.air,
		game->render_data.visual_ressources->air, game);
	set_position(game->render_data.air_count, game->render_data.air, 'L', game);
}

void	init_sprites(t_game *game)
{
	init_sprites_count(game);
	init_doors(game);
	init_targets(game);
	init_air(game);
	// check_sprites(game, &game->render_data, 0);
	// check_sprites(game, &game->render_data, 1);
	// check_sprites(game, &game->render_data, 2);
}

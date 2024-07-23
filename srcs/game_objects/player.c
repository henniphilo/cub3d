/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:05 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:21:06 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	set_player_pos(double x, double y, t_game *game)
{
	t_player	*player;

	player = &game->render.player;
	player->pos_x = x + 0.5;
	player->pos_y = y + 0.5;
}

void	set_player_dir(char direction, t_game *game)
{
	if (direction == 'N')
		set_north(game);
	else if (direction == 'E')
		set_east(game);
	else if (direction == 'S')
		set_south(game);
	else if (direction == 'W')
		set_west(game);
}

t_game	*set_player(t_game *game)
{
	int		x;
	int		y;
	char	direction;

	check_minimap(&game->minimap);
	y = 1;
	while (y < game->minimap.y_axis)
	{
		x = 1;
		while (x < game->minimap.x_axis[y])
		{
			direction = game->minimap.map[y][x];
			if (direction == 'N' || direction == 'E'
				|| direction == 'W' || direction == 'S')
			{
				set_player_dir(direction, game);
				set_player_pos(x, y, game);
				game->minimap.map[y][x] = '0';
				return (game);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

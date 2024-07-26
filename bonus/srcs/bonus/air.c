/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   air.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:47 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 13:18:33 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	is_air(t_render *render, int x, int y)
{
	int	i;

	i = 0;
	while (i < render->air_count)
	{
		if ((int)render->air[i].pos_x == x
			&& (int)render->air[i].pos_y == y)
			return (render->air[i].active);
		i++;
	}
	return (0);
}

static int	check_pos(t_render *render, int i, double next_x,
		double next_y)
{
	if (((int)render->air[i].pos_x == (int)next_x
			&& (int)render->air[i].pos_y == (int)render->player.pos_y)
		|| ((int)render->player.pos_x == (int)render->air[i].pos_x
			&& (int)next_y == (int)render->air[i].pos_y))
	{
		render->air[i].active = 0;
		render->count_oxy_caught += 1;
		return (1);
	}
	return (0);
}

void	get_air(t_game *game, t_minimap *minimap)
{
	t_player	*player;
	double		x;
	double		y;
	int			i;

	player = &game->render.player;
	x = (player->pos_x + player->dir_x * MOVE_SPEED);
	y = (player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	if ((minimap->map[(int)y][(int)player->pos_x] == 'L')
		|| minimap->map[(int)player->pos_y][(int)x] == 'L')
	{
		while (i < game->render.air_count)
		{
			if (check_pos(&game->render, i, x, y) == 1)
				break ;
			i++;
		}
		if (check_pos(&game->render, i, x, y) == 0)
			printf("Hurry! You need air!\n");
		else
			printf("You collected air! Well done! \n");
	}
}

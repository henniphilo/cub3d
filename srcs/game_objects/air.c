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

int	is_air(t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < render_data->air_count)
	{
		if ((int)render_data->air[i].pos_x == x
			&& (int)render_data->air[i].pos_y == y)
			return (render_data->air[i].active);
		i++;
	}
	return (0);
}

static int	check_pos(t_render_data *render_data, int i, double next_x,
		double next_y)
{
	if (((int)render_data->air[i].pos_x == (int)next_x
			&& (int)render_data->air[i].pos_y == (int)render_data->player.pos_y)
		|| ((int)render_data->player.pos_x == (int)render_data->air[i].pos_x
			&& (int)next_y == (int)render_data->air[i].pos_y))
	{
		render_data->air[i].active = 0;
		render_data->count_oxy_caught += 1;
		return (1);
	}
	return (0);
}

void	get_air(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	double		x;
	double		y;
	int			i;

	player = &game->render_data.player;
	x = (player->pos_x + player->dir_x * MOVE_SPEED);
	y = (player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	if ((map_data->map[(int)y][(int)player->pos_x] == 'L')
		|| map_data->map[(int)player->pos_y][(int)x] == 'L')
	{
		while (i < game->render_data.air_count)
		{
			if (check_pos(&game->render_data, i, x, y) == 1)
				break ;
			i++;
		}
		if (check_pos(&game->render_data, i, x, y) == 0)
			printf("Hurry! You need air!\n");
		else
			printf("You collected air! Well done! \n");
	}
}

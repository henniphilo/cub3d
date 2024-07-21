/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:16 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 13:19:57 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	is_target(t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < render_data->target_count)
	{
		if ((int)render_data->targets[i].pos_x == x
			&& (int)render_data->targets[i].pos_y == y)
			return (render_data->targets[i].active);
		i++;
	}
	return (0);
}

static int	check_pos(t_render_data *render_data, t_sprite *target, int next_x,
		int next_y)
{
	int	target_x;
	int	target_y;
	int	player_x;
	int	player_y;

	target_x = target->pos_x;
	target_y = target->pos_y;
	player_x = render_data->player.pos_x;
	player_y = render_data->player.pos_y;
	if ((target_x == (int)next_x && target_y == player_y)
		|| (player_x == target_x && (int)next_y == target_y))
	{
		target->active = 0;
		render_data->count_fish_caught += 1;
		return (1);
	}
	return (0);
}

void	log_target(t_sprite *target, int x, int y, t_render_data *render_data)
{
	if (check_pos(render_data, target, x, y) == 0)
		printf("oops you didn't get the fish. Try again!\n");
	else
		printf("You caught %d fish out of %d fish in the ocean \n",
			render_data->count_fish_caught, render_data->target_count);
}

void	get_target(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	t_sprite	*target;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (player->pos_x + player->dir_x * MOVE_SPEED);
	y = (player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	if (map_data->map[(int)y][(int)x] == 'T')
	{
		while (i < game->render_data.target_count)
		{
			target = &game->render_data.targets[i++];
			if (check_pos(&game->render_data, target, (int)x, (int)y) == 1)
				break ;
			log_target(target, x, y, &game->render_data);
		}
	}
}

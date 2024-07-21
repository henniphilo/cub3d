/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:48 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/19 13:18:50 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	is_door(t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < render_data->door_count)
	{
		if ((int)render_data->doors[i].pos_x == x
			&& (int)render_data->doors[i].pos_y == y)
			return (render_data->doors[i].active);
		i++;
	}
	return (0);
}

void	close_doors(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	if ((map_data->map[y][(int)player->pos_x + 1] == 'D')
		|| map_data->map[(int)player->pos_y + 1][x] == 'D'
		|| (map_data->map[y][(int)player->pos_x - 1] == 'D')
		|| map_data->map[(int)player->pos_y - 1][x] == 'D')
	{
		while (i < game->render_data.door_count)
		{
			game->render_data.doors[i].active = 1;
			i++;
		}
	}
}

static int	check_pos(t_render_data *render_data, int i, double next_x,
		double next_y)
{
	t_sprite	door;

	door = render_data->doors[i];
	if (((int)door.pos_x == (int)next_x
			&& (int)door.pos_y == (int)render_data->player.pos_y)
		|| ((int)render_data->player.pos_x == (int)door.pos_x
			&& (int)next_y == (int)door.pos_y))
	{
		render_data->doors[i].active = 0;
		return (1);
	}
	return (0);
}

void	open_doors(t_render_data *render_data, t_map_data *map_data)
{
	t_player	*player;
	double		next_x;
	double		next_y;
	int			i;

	player = &render_data->player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED;
	i = 0;
	if ((map_data->map[(int)next_y][(int)player->pos_x] == 'D')
		|| map_data->map[(int)player->pos_y][(int)next_x] == 'D')
	{
		while (i < render_data->door_count)
		{
			if (check_pos(render_data, i, next_x, next_y) == 1)
				break ;
			i++;
		}
		if (check_pos(render_data, i, next_x, next_y) == 0)
			printf("hmm the door ain't open yet. Try again!\n");
		else
			printf("You opend the door! Yey!\n");
	}
}

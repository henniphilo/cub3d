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

int	is_door(t_render *render, int x, int y)
{
	int	i;

	i = 0;
	while (i < render->door_count)
	{
		if ((int)render->doors[i].pos_x == x
			&& (int)render->doors[i].pos_y == y)
			return (render->doors[i].active);
		i++;
	}
	return (0);
}

void	close_doors(t_game *game, t_minimap *minimap)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	i = 0;
	if ((minimap->map[y][(int)player->pos_x + 1] == 'D')
		|| minimap->map[(int)player->pos_y + 1][x] == 'D'
		|| (minimap->map[y][(int)player->pos_x - 1] == 'D')
		|| minimap->map[(int)player->pos_y - 1][x] == 'D')
	{
		while (i < game->render.door_count)
		{
			game->render.doors[i].active = 1;
			i++;
		}
	}
}

static int	check_pos(t_render *render, int i, double next_x,
		double next_y)
{
	t_sprite	door;

	door = render->doors[i];
	if (((int)door.pos_x == (int)next_x
			&& (int)door.pos_y == (int)render->player.pos_y)
		|| ((int)render->player.pos_x == (int)door.pos_x
			&& (int)next_y == (int)door.pos_y))
	{
		render->doors[i].active = 0;
		return (1);
	}
	return (0);
}

void	open_doors(t_render *render, t_minimap *minimap)
{
	t_player	*player;
	double		next_x;
	double		next_y;
	int			i;

	player = &render->player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED;
	i = 0;
	if ((minimap->map[(int)next_y][(int)player->pos_x] == 'D')
		|| minimap->map[(int)player->pos_y][(int)next_x] == 'D')
	{
		while (i < render->door_count)
		{
			if (check_pos(render, i, next_x, next_y) == 1)
				break ;
			i++;
		}
		if (check_pos(render, i, next_x, next_y) == 0)
			printf("hmm the door ain't open yet. Try again!\n");
		else
			printf("You opend the door! Yey!\n");
	}
}

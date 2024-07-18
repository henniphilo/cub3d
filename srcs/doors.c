/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:19:48 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:19:50 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	is_door(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	// printf("is door check x %d y %d \n", x, y);
	while (i < game->render_data.count_door)
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
		while (i < game->render_data.count_door)
		{
			game->render_data.doors[i].active = 1;
			i++;
		}
	}
}

void	open_doors(t_game *game, t_render_data *render_data,
		t_map_data *map_data)
{
	t_player	*player;
	double		next_x;
	double		next_y;
	int			i;

	(void)render_data;
	player = &game->render_data.player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED;
	printf("next x %d y %d \n", (int)next_x, (int)next_y);
	i = 0;
	if ((map_data->map[(int)next_y][(int)player->pos_x] == 'D')
		|| map_data->map[(int)player->pos_y][(int)next_x] == 'D')
	{
		while (i < game->render_data.count_door)
		{
			if (((int)game->render_data.doors[i].pos_x == (int)next_x
					&& (int)game->render_data.doors[i].pos_y == (int)player->pos_y)
				|| ((int)player->pos_x == (int)game->render_data.doors[i].pos_x
					&& (int)next_y == (int)game->render_data.doors[i].pos_y))
			{
				game->render_data.doors[i].active = 0;
				printf("door open\n");
				break ;
			}
			i++;
		}
	}
	printf("hmm the door ain't open yet. Try again!\n");
}

#include "../incl/cub3d.h"

int	is_target(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->render_data.count_target)
	{
		if ((int)render_data->targets[i].pos_x == x
			&& (int)render_data->targets[i].pos_y == y)
			return (render_data->targets[i].active);
		i++;
	}
	return (0);
}

void	get_target(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	double		x;
	double		y;
	int			i;

	player = &game->render_data.player;
	x = (player->pos_x + player->dir_x * MOVE_SPEED);
	y = (player->pos_y + player->dir_y * MOVE_SPEED);
	printf("player x: %d y: %d \n", (int)x, (int)y);
	i = 0;
	if ((map_data->map[(int)y][(int)player->pos_x] == 'T')
		|| map_data->map[(int)player->pos_y][(int)x] == 'T')
	{
		while (i < game->render_data.count_target)
		{
			if ((int)game->render_data.targets[i].pos_x == (int)x
				&& (int)game->render_data.targets[i].pos_y == (int)y)
			{
				game->render_data.targets[i].active = 0;
				game->render_data.count_fish_caught += 1;
				printf("got target\n");
				break ;
			}
			i++;
		}
	}
	printf("oops you didn't get the fish. Try again!\n");
}

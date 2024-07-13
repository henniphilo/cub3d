#include "../incl/cub3d.h"

int	is_door_open(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if ((int)render_data->doors[i].pos_x == x
			&& (int)render_data->doors[i].pos_y == y)
			return (render_data->doors[i].open_door);
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
	// printf("Player position: pos_x = %.2f, pos_y = %.2f\n", player->pos_x,
	// player->pos_y);
	// printf("Checking positions: [%d][%d+1], [%d+1][%d], [%d][%d-1],
	// [%d-1][%d]\n", (int)player->pos_x, y, x, (int)player->pos_y,
	// (int)player->pos_x, y, x, (int)player->pos_y);
	if ((x >= 0 && x < map_data->width) && (y >= 0 && y < map_data->height))
	{
		if ((map_data->map[y][(int)player->pos_x + 1] == 'D')
			|| map_data->map[(int)player->pos_y + 1][x] == 'D'
			|| (map_data->map[y][(int)player->pos_x - 1] == 'D')
			|| map_data->map[(int)player->pos_y - 1][x] == 'D')
		{
			while (i < game->door_count)
			{
				// if (game->render_data.do_sprites[i].open_door == 1)
				// {
				game->render_data.doors[i].open_door = 0;
				printf("door closed\n");
				//	break ;
				// }
				i++;
			}
		}
	}
	else
		printf("Position out of bounds: x = %d, y = %d\n", x, y);
}

void	open_doors(t_game *game, t_render_data *render_data,
		t_map_data *map_data)
{
	t_player	*player;
	double			next_x;
	double			next_y;
	int			i;

	(void)render_data;
	player = &game->render_data.player;
	next_x = player->pos_x + player->dir_x * MOVE_SPEED;
	next_y = player->pos_y + player->dir_y * MOVE_SPEED;
	i = 0;
	if ((map_data->map[(int)next_y][(int)player->pos_x] == 'D')
		|| map_data->map[(int)player->pos_y][(int)next_x] == 'D')
	{
		while (i < game->door_count)
		{
			if (((int)game->render_data.doors[i].pos_x == (int)next_x
				&& (int) game->render_data.doors[i].pos_y == (int)player->pos_y)
				|| ((int)player->pos_x == (int)game->render_data.doors[i].pos_x
				&& (int)next_y == game->render_data.doors[i].pos_y))
			{
				game->render_data.doors[i].open_door = 1;
				printf("door open\n");
				break ;
			}
			i++;
		}
	}
	printf("hmm the door ain't open yet. Try again!\n");
}

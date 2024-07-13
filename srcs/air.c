#include "../incl/cub3d.h"

int	is_get_air(t_game *game, t_render_data *render_data, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->air_caught)
	{
		if ((int)render_data->air_sprites[i].pos_x == x
			&& (int)render_data->air_sprites[i].pos_y == y)
			return (render_data->air_sprites[i].got_air);
		i++;
	}
	return (0);
}



void	get_air(t_game *game, t_map_data *map_data)
{
	t_player	*player;
	int			x;
	int			y;
	int			i;

	player = &game->render_data.player;
	x = (int)(player->pos_x + player->dir_x * MOVE_SPEED);
	y = (int)(player->pos_y + player->dir_y * MOVE_SPEED);
	printf("air x: %d y: %d \n", x, y);
	i = 0;
	if ((map_data->map[y][(int)player->pos_x] == 'L')
		|| map_data->map[(int)player->pos_y][x] == 'L')
	{
		//	render_data->sprites.open_door = 1;
		while (i < game->air_count)
		{
			if (game->render_data.air_sprites[i].pos_x == x
				&& game->render_data.air_sprites[i].pos_y == y)
			{
				game->render_data.air_sprites[i].got_air = 1;
				game->air_caught += 1;
				//	add_look(game, game->visual_res.bubbles, WINDOW_HEIGHT / 2,
						// WINDOW_HEIGHT);
						printf("got air\n");
						print_got_air(game);
						break ;
			}
			i++;
		}
	}
	printf("Hurry! You need air!\n");
}
#include "../incl/cub3d.h"

void	set_player_pos(double x, double y, t_game *game)
{
	t_player	*player;

	player = &game->render_data.player;
	player->pos_x = x;
	player->pos_y = y;
	player->prev_pos_x = player->pos_x;
	player->prev_pos_y = player->pos_y;
	printf("set player pos x = %.2f  y = %.2f \n", player->pos_x, player->pos_y);
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

	printf("in init player\n");
	y = 1;
	while (y < game->map_data.y_axis)
	{
		x = 0;
		while (x < game->map_data.x_axis[y])
		{
			direction = game->map_data.map[y][x];
			if (direction == 'N' || direction == 'E'
				|| direction == 'W' || direction == 'S')
			{
				printf("x init ist %d und y init ist %d \n", y , x);
				set_player_dir(direction, game);
				set_player_pos(x, y, game);
				return (game);
			}
			x++;
		}
		y++;
	}
	printf("first dir is %c\n", game->map_data.first_dir);
	return (NULL);
}


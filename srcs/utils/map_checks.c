#include "../../incl/cub3d.h"

int	map_input_check(t_game *game)
{
	cub_input(game);
	which_color(game);
	actual_map(game);
	free_cub(game);
	if(!game->look.EA || !game->look.NO || !game->look.SO
		|| !game->look.WE || !game->look.ceiling || !game->look.floor)
	{
		free_data(game);
		return (1);
	}
	if ((walls_check(game)) == 1)
	{
		perror("Error walls fail\n");
		exit(1);
	}
	return (0);
}

int	walls_check(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	int		height;

	i = 0;
	j = 1;
	height = game->map.y_axis;
	map = game->map.map;
	//printf("game->map.x_axis[0]: %d\n", game->map.x_axis[0]);
	while (i < game->map.x_axis[0] && map[0][i] != '\n')
	{
		if(map[0][i] != '1')
		{
			printf("Top border error at position (0, %d): map[0][%d] = %c\n", i, i, map[0][i]);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < game->map.x_axis[height - 1] && map[height - 1][i] != '\n')
	{
		if (map[height - 1][i] != '1' && map[height - 1][i] != ' ')
		{
			printf("Bottom border error at position (%d, %d): map[%d][%d] = %c\n", height - 1, i, height - 1, i, map[height - 1][i]);
			return (1);
		}
		i++;
	}
	while (j < height - 1 && map[j][game->map.x_axis[j] - 1] != '\n')
	{
		if (map[j][0] != '1' || map[j][game->map.x_axis[j] - 1] != '1')
		{
			printf("Left border error at position (%d, 0): map[%d][0] = %c\n", j, j, map[j][0]);
			printf("Right border error at position (%d, %d): map[%d][%d] = %c\n", j, game->map.x_axis[j] - 1, j, game->map.x_axis[j] - 1, map[j][game->map.x_axis[j] - 1]);
			return (1);
		}
		j++;
	}
	return (0);
}


int	check_map_cub(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i--;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c'
		|| file[i - 3] != '.')
	{
		return (1);
	}
	return (0);
}




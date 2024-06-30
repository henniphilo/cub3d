#include "../../incl/cub3d.h"


static int	check_top(t_game *game, char **map)
{
	int		i;

	i = 0;
	while (i < game->map.x_axis[0] && map[0][i] != '\n')
	{
		if(map[0][i] != '1')
		{
			printf("Top border error at position (0, %d): map[0][%d] = %c\n", i, i, map[0][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_bottom(t_game *game, char **map)
{
	int		i;
	int		height;
	;

	i = 0;
	height = game->map.y_axis;
	while (i < game->map.x_axis[height - 1] && map[height - 1][i] != '\n')
	{
		if (map[height - 1][i] != '1' && map[height - 1][i] != ' ')
		{
			printf("Bottom border error at position (%d, %d): map[%d][%d] = %c\n", height - 1, i, height - 1, i, map[height - 1][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_sides(t_game *game, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j < game->map.y_axis - 1 && map[j][game->map.x_axis[j] - 1] != '\n')
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

int	walls_check(t_game *game)
{
	char	**map;

	map = game->map.map;
	if (check_bottom(game, map))
		return (1);
	if (check_top(game, map))
		return (1);
	if (check_sides(game, map))
		return (1);
	return (0);
}

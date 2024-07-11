#include "../../incl/cub3d.h"


static int	check_top(t_map_data *map_data)
{
	int		i;

	i = 0;
	while (i < map_data->x_axis[0] && map_data->map[0][i] != '\n')
	{
		if(map_data->map[0][i] != '1')
		{
			printf("Top border error at position (0, %d): map[0][%d] = %c\n", i, i, map_data->map[0][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_bottom(t_map_data *map_data)
{
	int		i;
	int		height;
	;

	i = 0;
	height = map_data->y_axis;
	while (i < map_data->x_axis[height - 1] && map_data->map[height - 1][i] != '\n')
	{
		if (map_data->map[height - 1][i] != '1' && map_data->map[height - 1][i] != ' ')
		{
			printf("Bottom border error at position (%d, %d): map[%d][%d] = %c\n", height - 1, i, height - 1, i, map_data->map[height - 1][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_sides(t_map_data *map_data)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j < map_data->y_axis - 1 && map_data->map[j][map_data->x_axis[j] - 1] != '\n')
	{
		if (map_data->map[j][0] != '1' || map_data->map[j][map_data->x_axis[j] - 1] != '1')
		{
			printf("Left border error at position (%d, 0): map[%d][0] = %c\n", j, j, map_data->map[j][0]);
			printf("Right border error at position (%d, %d): map[%d][%d] = %c\n", j, map_data->x_axis[j] - 1, j, map_data->x_axis[j] - 1, map_data->map[j][map_data->x_axis[j] - 1]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	walls_check(t_map_data *map_data)
{
	if (check_bottom(map_data))
		return (1);
	if (check_top(map_data))
		return (1);
	if (check_sides(map_data))
		return (1);
	return (0);
}

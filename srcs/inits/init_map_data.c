#include "../../incl/cub3d.h"

t_map_data	init_map_data(void)
{
	t_map_data	map;

	map.input_table = NULL;
	map.height = 0;
	map.width = 0;
	map.map = NULL;
	map.player = NULL;
	map.x_axis = 0;
	map.y_axis = 0;
	return (map);
}
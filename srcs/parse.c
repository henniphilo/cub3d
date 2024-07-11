#include "../incl/cub3d.h"

int	parse(t_game *game, char **argv)
{
	open_map(game, argv[1]);
	if (!game->map_data.map)
		return (1); ///TODO: handle clean exit
	return (0);
}
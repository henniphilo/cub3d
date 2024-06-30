#include "../../incl/cub3d.h"

void	free_cub(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.cub[i]);
		i++;
	}
	free(game->map.cub);
}

void	free_data(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.y_axis)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	free(game->look.NO);
	free(game->look.SO);
	free(game->look.WE);
	free(game->look.EA);
	free(game->look.ceiling);
	free(game->look.floor);
}

#include "../../incl/cub3d.h"

void	cub_input(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (ft_strncmp(game->map.cub[y], "NO ", 3) == 0)
		{
			game->look.NO = get_from_cub(game->map.cub[y], "NO");
		}
		if (ft_strncmp(game->map.cub[y], "SO ", 3) == 0)
		{
			game->look.SO = get_from_cub(game->map.cub[y], "SO");
		}
		if (ft_strncmp(game->map.cub[y], "WE ", 3) == 0)
		{
			game->look.WE = get_from_cub(game->map.cub[y], "WE");
		}
		if (ft_strncmp(game->map.cub[y], "EA ", 3) == 0)
		{
			game->look.EA = get_from_cub(game->map.cub[y], "EA");
		}
		y++;
	}
	printf("NO: %s\n", game->look.NO);
	printf("SO: %s\n", game->look.SO);
	printf("WE: %s\n", game->look.WE);
	printf("EA: %s\n", game->look.EA);
}

void	which_color(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		if (ft_strncmp(game->map.cub[y], "F ", 2) == 0)
		{
			game->look.floor = get_from_cub(game->map.cub[y], "F");
		}
		if (ft_strncmp(game->map.cub[y], "C ", 2) == 0)
		{
			game->look.ceiling = get_from_cub(game->map.cub[y], "C");
		}
		y++;
	}
	printf("floor: %s\n", game->look.floor);
	printf("ceiling: %s\n", game->look.ceiling);
}


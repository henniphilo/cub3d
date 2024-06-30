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




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

	printf("in free data\n");
	i = 0;
	while (i < game->map.y_axis)
	{
		free(game->map.map[i]);
		i++;
	}
	if (game->map.x_axis)
			free(game->map.x_axis);
	// if (game->map.cub)
	// 		free_string_arr(game->map.cub);
	//clean_texture(game);
	free(game->map.map);
	free(game->look.NO);
	free(game->look.SO);
	free(game->look.WE);
	free(game->look.EA);
	free(game->look.door);
	free(game->look.ceiling);
	free(game->look.floor);
}

void	free_string_arr(char **string_arr)
{
	int	i;

	i = 0;
	while (string_arr[i])
	{
		free(string_arr[i]);
		i++;
	}
	free(string_arr);
}

int	terminate_game(t_game *game, int exit_code)
{
	if (game)
	{
		free_data(game);
		if (game->mlx_ptr)
		{
			if (game->img)
				mlx_delete_image(game->mlx_ptr, game->img);
			mlx_terminate(game->mlx_ptr);
		}
		if (game->map.cub)
			free_string_arr(game->map.cub);
		if (game->map.map)
			free_string_arr(game->map.map);
		if (game->map.x_axis)
			free(game->map.x_axis);
	}
	return (exit_code);
}

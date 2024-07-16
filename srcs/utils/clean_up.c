#include "../../incl/cub3d.h"

void	free_input_table(int map_height, char **input_table)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(input_table[i]);
		i++;
	}
	free(input_table);
}

void	free_data(t_game *game)
{
	int	i;

	printf("in free data\n");
	i = 0;
	while (i < game->map_data.y_axis)
	{
		// free(game->map_data.map[i]);
		i++;
	}
	// if (game->map_data.x_axis)
	// 		free(game->map_data.x_axis);


	//clean_texture(game);
	free(game->map_data.map);
	free(game->visual_res.NO);
	free(game->visual_res.SO);
	free(game->visual_res.WE);
	free(game->visual_res.EA);
	free(game->visual_res.bubbles);
	free(game->visual_res.target);
	free(game->visual_res.door);
	free(game->visual_res.air);
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
			if (game->render_data.screen_image)
				mlx_delete_image(game->mlx_ptr, game->render_data.screen_image);
			mlx_terminate(game->mlx_ptr);
		}
		if (game->map_data.input_table)
			free_string_arr(game->map_data.input_table);
		if (game->map_data.map)
			free_string_arr(game->map_data.map);
		if (game->map_data.x_axis)
			free(game->map_data.x_axis);
	}
	exit(exit_code);
}

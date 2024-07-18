#include "../incl/cub3d.h"

int	check_game_param(t_game *game)
{
	if (!game)
		return (-1);
	if (game->mlx_ptr == NULL)
		return (-1);
	if (check_map_data(&game->map_data))
		return (-1);
	if (check_render_data(&game->render_data))
		return (-1);
	if (check_visual(&game->visual_res))
		return (-1);
	return (0);
}

int	check_map_data(t_map_data *map_data)
{
	char	first_dir;

	if (map_data == NULL)
		return (-1);
	if (map_data->height < 0 || map_data->width < 0 || map_data->y_axis < 0)
		return (-1);
	if (map_data->input_table == NULL)
		return (-1);
	if (map_data->map == NULL)
		return (-1);
	if (map_data->x_axis == NULL)
		return (-1);
	first_dir = map_data->first_dir;
	if (first_dir != 'N' && first_dir != 'S' && first_dir != 'E'
		&& first_dir != 'W')
		return (-1);
	return (0);
}

int	check_render_data(t_render_data *render_data)
{
	if (render_data == NULL)
		return (-1);
	if (render_data->doors == NULL)
		return (-1);
	if (render_data->oxygen_tanks == NULL)
		return (-1);
	if (render_data->vis == NULL)
		return (-1);
	if (render_data->targets == NULL)
		return (-1);
	if (render_data->screen_image == NULL)
		return (-1);
	return (0);
}

int	check_visual(t_visual *vis)
{
	if (vis == NULL)
		return (-1);
	if (vis->air == NULL)
		return (-1);
	// if (vis->bubbles == NULL)
	// 	return (-1);
	// if (vis->bubbles_img == NULL)
	// 	return (-1);
	if (vis->door == NULL)
		return (-1);
	if (vis->ea == NULL)
		return (-1);
	if (vis->so == NULL)
		return (-1);
	if (vis->no == NULL)
		return (-1);
	if (vis->we == NULL)
		return (-1);
	// if (vis->player == NULL)
	// 	return (-1);
	if (vis->target == NULL)
		return (-1);
	// if (vis->target_img == NULL)
	// 	return (-1);
	return (0);
}

void	argv_check(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./cube [mapfile.cub]\n");
		exit(EXIT_FAILURE);
	}
	if (check_file_type(argv[1]))
	{
		printf("Error: Input file is not .cub \n");
		terminate_game(NULL, EXIT_FAILURE);
	}
}

#include "../../incl/cub3d.h"

int	parse_input_table(t_game *game)
{
	t_texpaths paths;

	paths = init_texpaths();
	parse_paths(game->map_data.height, &paths, game->map_data.input_table);
	if(!paths.EA || !paths.NO || !paths.SO
		|| !paths.WE || !paths.ceiling)
	{
		exit(1); // ? TODO: clean exit strategy
		return (1);
	}
	load_visuals(&game->visual_res, &paths);
	game->render_data.vis = &game->visual_res;
	create_map(&game->map_data);
	free_input_table(game->map_data.height, game->map_data.input_table);

	if ((walls_check(&game->map_data)) == 1)
	{
		perror("Error walls fail\n");
		exit(1);
	}
	return (0);
}

int	check_file_ending_cub(char *file)
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




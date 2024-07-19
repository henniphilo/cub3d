/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:40:12 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/18 17:40:16 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	parse_input_table(t_game *game)
{
	t_texpaths	paths;

	paths = init_texpaths();
	parse_paths(game->map_data.height, &paths, game->map_data.input_table);
	if (!paths.ea || !paths.no || !paths.so || !paths.we || !paths.ceiling)
	{
		ft_putendl_fd("Error: Textures missing", STDERR_FILENO);
		return (-1);
	}
	load_visuals(&game->visual_res, &paths);
	game->render_data.vis = &game->visual_res;
	create_map(game);
	free_input_table(game->map_data.height, game->map_data.input_table);
	if ((walls_check(&game->map_data)) == 1)
	{
		ft_putendl_fd("Error: Walls fail", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	check_file_type(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	i--;
	if (file[i] != 'b' || file[i - 1] != 'u' || file[i - 2] != 'c' || file[i
			- 3] != '.')
	{
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:40:12 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/23 16:02:16 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	parse_input_table(t_game *game)
{
	t_texpaths	paths;

	paths = init_texpaths();
	parse_paths(game->minimap.height, &paths, game->minimap.input_table);
	if (!paths.ea || !paths.no || !paths.so || !paths.we || !paths.ceiling)
	{
		ft_putendl_fd("Error: Textures missing", STDERR_FILENO);
		return (-1);
	}
	load_visuals(&game->render.res, &paths);
	free_paths(&paths);
	create_map(game);
	free_input_table(game->minimap.height, game->minimap.input_table);
	if ((walls_check(&game->minimap)) == 1)
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

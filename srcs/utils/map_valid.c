/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:50 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:17:51 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	open_map(t_game *game, char *file)
{
	// if (check_game_param(game) == -1)
	// 	terminate_game(game, EXIT_FAILURE);
	if (check_file_type(file))
		terminate_game(game, EXIT_FAILURE);
	if (init_input_table(&game->map_data, file) == -1
		|| fill_input_table(&game->map_data, file) == -1
		|| parse_input_table(game) == -1)
		terminate_game(game, EXIT_FAILURE);
}

int	get_map_start(unsigned int map_height, char **input_table)
{
	int				y;
	int				is_line;
	unsigned int	map_start;
	char			*line;

	map_start = 0;
	while (map_start < map_height)
	{
		line = input_table[map_start];
		is_line = 1;
		y = 0;
		while (line[y] != '\0')
		{
			if (line[y] != ' ' && line[y] != '1' && line[y] != '\n')
			{
				is_line = 0;
				break ;
			}
			y++;
		}
		if (is_line && y > 1)
			break ;
		(map_start)++;
	}
	return (map_start);
}

static int	init_map(t_map_data *map_data, int map_start)
{
	map_data->y_axis = map_data->height - map_start;
	map_data->map = (char **)ft_calloc((map_data->y_axis + 1), sizeof(char *));
	map_data->x_axis = (int *)ft_calloc(map_data->y_axis, sizeof(int));
	if (!map_data->map || !map_data->x_axis)
		return (-1);
	return (1);
}

void	create_map(t_game *game)
{
	int		y;
	int		map_start;
	char	**input_table;

	map_start = get_map_start(game->map_data.height,
			game->map_data.input_table);
	if (init_map(&game->map_data, map_start) == -1)
		terminate_game(game, EXIT_FAILURE);
	y = 0;
	while (y < game->map_data.y_axis)
	{
		input_table = game->map_data.input_table;
		game->map_data.map[y] = ft_strdup(input_table[map_start + y]);
		if (!game->map_data.map[y])
		{
			ft_putendl_fd("Error in dup line \n", STDERR_FILENO);
			terminate_game(game, EXIT_FAILURE);
		}
		game->map_data.x_axis[y] = ft_strlen(game->map_data.map[y]);
		y++;
	}
	game->map_data.map[game->map_data.y_axis] = NULL;
}

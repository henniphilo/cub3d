/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:42:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/19 11:52:57 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(game->map_data.map);
	free(game->visual_res.no);
	free(game->visual_res.so);
	free(game->visual_res.we);
	free(game->visual_res.ea);
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
		clean_img(game);
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

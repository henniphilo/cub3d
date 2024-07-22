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

void	free_map_data(t_minimap *map)
{
	(void)map;
}

void	free_visual_res(t_ressources *res)
{
	(void)res;
}

void	free_render_data(t_render *render)
{
	(void)render;
}

void	free_data(t_game *game)
{

	free_map_data(&game->minimap);
	free_visual_res(&game->render.res);
	free_render_data(&game->render);
	if (game->mlx_ptr == NULL)
		return ;
// 	return (0);
// }

// int	check_map_data(t_map_data *minimap)
// {
// 	char	first_dir;

// 	if (minimap == NULL)
// 		return (-1);
// 	if (minimap->height < 0 || minimap->width < 0 || minimap->y_axis < 0)
// 		return (-1);
// 	if (minimap->input_table == NULL)
// 		return (-1);
// 	if (minimap->map == NULL)
// 		return (-1);
// 	if (minimap->x_axis == NULL)
// 		return (-1);
// 	first_dir = minimap->first_dir;
// 	if (first_dir != 'N' && first_dir != 'S' && first_dir != 'E'
// 		&& first_dir != 'W')
// 		return (-1);
// 	return (0);
// }

// int	check_render_data(t_render_data *render)
// {
// 	if (render == NULL)
// 		return (-1);
// 	if (render->doors == NULL)
// 		return (-1);
// 	if (render->air == NULL)
// 		return (-1);
// 	if (render->visual_ressources == NULL)
// 		return (-1);
// 	if (render->targets == NULL)
// 		return (-1);
// 	if (render->screen_image == NULL)
// 		return (-1);
// 	return (0);
// }

// int	check_visual(t_ressources *vis)
// {
// 	if (vis == NULL)
// 		return (-1);
// 	if (vis->air == NULL)
// 		return (-1);
// 	// if (vis->bubbles == NULL)
// 	// 	return (-1);
// 	// if (vis->bubbles_img == NULL)
// 	// 	return (-1);
// 	if (vis->door == NULL)
// 		return (-1);
// 	if (vis->ea == NULL)
// 		return (-1);
// 	if (vis->so == NULL)
// 		return (-1);
// 	if (vis->no == NULL)
// 		return (-1);
// 	if (vis->we == NULL)
// 		return (-1);
// 	// if (vis->player == NULL)
// 	// 	return (-1);
// 	if (vis->target == NULL)
// 		return (-1);
// 	// if (vis->target_img == NULL)
// 	// 	return (-1);
// 	return (0);
// }

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
			if (game->render.screen_image)
				mlx_delete_image(game->mlx_ptr, game->render.screen_image);
			mlx_terminate(game->mlx_ptr);
		}
		if (game->minimap.input_table)
			free_string_arr(game->minimap.input_table);
		if (game->minimap.map)
			free_string_arr(game->minimap.map);
		if (game->minimap.x_axis)
			free(game->minimap.x_axis);
	}
	exit(exit_code);
}

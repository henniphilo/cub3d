/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:42:42 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/21 14:42:44 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_game_param(t_game *game)
{
	if (!game)
		return (-1);
	if (game->mlx_ptr == NULL)
		return (-1);
	if (check_map_data(&game->minimap))
		return (-1);
	if (check_render_data(&game->render))
		return (-1);
	return (0);
}

int	check_map_data(t_minimap *minimap)
{
	char	first_dir;

	if (minimap == NULL)
		return (-1);
	if (minimap->height < 0 || minimap->width < 0 || minimap->y_axis < 0)
		return (-1);
	if (minimap->input_table == NULL)
		return (-1);
	if (minimap->map == NULL)
		return (-1);
	if (minimap->x_axis == NULL)
		return (-1);
	first_dir = minimap->first_dir;
	if (first_dir != 'N' && first_dir != 'S' && first_dir != 'E'
		&& first_dir != 'W')
		return (-1);
	return (0);
}


int	check_visual_res(t_ressources *vis)
{
	if (vis == NULL)
		return (-1);
	if (vis->air == NULL)
		return (-1);
	if (vis->bubbles == NULL)
		return (-1);
	if (vis->bubbles_img == NULL)
		return (-1);
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
	if (vis->player == NULL)
		return (-1);
	if (vis->target == NULL)
		return (-1);
	if (vis->target_img == NULL)
		return (-1);
	return (0);
}

int	check_render_data(t_render *render)
{
	if (render == NULL)
		return (-1);
	if (render->doors == NULL)
		return (-1);
	if (render->air == NULL)
		return (-1);
	if (render->targets == NULL)
		return (-1);
	if (render->screen_image == NULL)
		return (-1);
	if (check_visual_res(&render->res))
		return (-1);
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

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

void	free_minimap(t_minimap *map)
{
	if (map)
	{
		if (map->map)
			free_string_arr(map->map);
		if (map->x_axis)
			free(map->x_axis);
	}
}

void	free_ressources(t_ressources *res, mlx_t *mlx)
{
	if (res)
	{
		if (res->air)
			mlx_delete_texture(res->air);
		if (res->bubbles)
			mlx_delete_texture(res->bubbles);
		if (res->door)
			mlx_delete_texture(res->door);
		if (res->ea)
			mlx_delete_texture(res->ea);
		if (res->so)
			mlx_delete_texture(res->so);
		if (res->no)
			mlx_delete_texture(res->no);
		if (res->we)
			mlx_delete_texture(res->we);
		if (res->target)
			mlx_delete_texture(res->target);
		if (res->bubbles_img)
			mlx_delete_image(mlx, res->bubbles_img);
	}
}

void	free_render(t_render *render)
{
	if (render)
	{
		if (render->doors)
			free(render->doors);
		if (render->air)
			free(render->air);
		if (render->targets)
			free(render->targets);
		if (render->screen_image)
			mlx_delete_image(render->mlx_ptr, render->screen_image);
		if (render->mlx_ptr)
			mlx_close_window(render->mlx_ptr);
	}
}

void	free_data(t_game *game)
{
	free_minimap(&game->minimap);
	free_ressources(&game->render.res, game->render.mlx_ptr);
	free_render(&game->render);
}

int	terminate_game(t_game *game, int exit_code)
{
	if (game)
		free_data(game);
	exit(exit_code);
}

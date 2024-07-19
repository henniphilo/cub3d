/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:15 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:32:23 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	load_visuals(t_visual *visual_res, t_texpaths *paths)
{
	if (paths->no)
		visual_res->no = mlx_load_png(paths->no);
	if (paths->so)
		visual_res->so = mlx_load_png(paths->so);
	if (paths->we)
		visual_res->we = mlx_load_png(paths->we);
	if (paths->ea)
		visual_res->ea = mlx_load_png(paths->ea);
	if (!visual_res->no || !visual_res->we
		|| !visual_res->so || !visual_res->ea)
	{
		printf("texture are missing\n");
		exit (1);
	}
	visual_res->door = mlx_load_png(DOOR_PATH);
	if (!visual_res->door)
		printf("door texture missing\n");
	visual_res->target = mlx_load_png(TARGET_PATH);
	if (!visual_res->target)
		printf("target texture missing\n");
	visual_res->air = mlx_load_png(AIR_PATH);
	if (!visual_res->air)
		printf("air texture missing\n");
	visual_res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	visual_res->c_floor = int_to_color(get_color_int(paths->floor));
}

void	clean_texture(t_game *game)
{
	if (game->visual_res.no)
		mlx_delete_texture(game->visual_res.no);
	if (game->visual_res.so)
		mlx_delete_texture(game->visual_res.so);
	if (game->visual_res.we)
		mlx_delete_texture(game->visual_res.we);
	if (game->visual_res.ea)
		mlx_delete_texture(game->visual_res.ea);
	if (game->visual_res.door)
		mlx_delete_texture(game->visual_res.door);
	if (game->visual_res.target)
		mlx_delete_texture(game->visual_res.target);
	if (game->visual_res.player)
		mlx_delete_texture(game->visual_res.player);
	if (game->visual_res.air)
		mlx_delete_texture(game->visual_res.air);
}

void	clean_img(t_game *game)
{
	mlx_delete_image(game->mlx_ptr, game->visual_res.bubbles_img);
}

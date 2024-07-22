/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:15 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/19 12:29:49 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	load_visuals(t_ressources *res, t_texpaths *paths)
{
	if (paths->no)
		res->no = mlx_load_png(paths->no);
	if (paths->so)
		res->so = mlx_load_png(paths->so);
	if (paths->we)
		res->we = mlx_load_png(paths->we);
	if (paths->ea)
		res->ea = mlx_load_png(paths->ea);
	if (!res->no || !res->we
	|| !res->so || !res->ea)
	{
		printf("texture are missing\n");
		exit (1);
	}
	res->door = mlx_load_png(DOOR_PATH);
	if (!res->door)
		printf("door texture missing\n");
	res->target = mlx_load_png(TARGET_PATH);
	if (!res->target)
		printf("target texture missing\n");
	res->air = mlx_load_png(AIR_PATH);
	if (!res->air)
		printf("air texture missing\n");
	res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	res->c_floor = int_to_color(get_color_int(paths->floor));
}

void	clean_texture(t_game *game)
{
	if (game->render.res.no)
		mlx_delete_texture(game->render.res.no);
	if (game->render.res.so)
		mlx_delete_texture(game->render.res.so);
	if (game->render.res.we)
		mlx_delete_texture(game->render.res.we);
	if (game->render.res.ea)
		mlx_delete_texture(game->render.res.ea);
	if (game->render.res.door)
		mlx_delete_texture(game->render.res.door);
	if (game->render.res.target)
		mlx_delete_texture(game->render.res.target);
	if (game->render.res.player)
		mlx_delete_texture(game->render.res.player);
	if (game->render.res.air)
		mlx_delete_texture(game->render.res.air);
}

void	clean_img(t_game *game)
{
	mlx_delete_image(game->mlx_ptr, game->render.res.bubbles_img);
}

void	init_look(t_game *game)
{
	game->minimap.cair = int_to_color(get_color_int(C_AIR));
	game->minimap.cblue = int_to_color(get_color_int(C_BLUE));
	game->minimap.cdoor = int_to_color(get_color_int(C_DOOR));
	game->minimap.cfloor = int_to_color(get_color_int(C_FLOOR));
	game->minimap.cwall = int_to_color(get_color_int(C_WALL));
	game->minimap.ctarget = int_to_color(get_color_int(C_TARGET));
	game->minimap.cside = int_to_color(get_color_int(C_SIDE));
	game->minimap.cplayer = int_to_color(get_color_int(C_PLAYER));
	game->minimap.ctransparent.r = 0;
	game->minimap.ctransparent.g = 0;
	game->minimap.ctransparent.b = 0;
	game->minimap.ctransparent.a = 0;
}

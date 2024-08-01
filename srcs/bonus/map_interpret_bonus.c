/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_interpret_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:15 by hwiemann          #+#    #+#             */
/*   Updated: 2024/08/01 11:41:03 by hwiemann         ###   ########.fr       */
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
	if (!res->no || !res->we || !res->so || !res->ea)
	{
		printf("Error texture are missing\n");
		exit(1);
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
	printf("ceiling: ");
	res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	printf("floor: ");
	res->c_floor = int_to_color(get_color_int(paths->floor));
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

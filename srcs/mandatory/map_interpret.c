/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:15 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/26 11:57:22 by hwiemann         ###   ########.fr       */
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
		printf("texture are missing\n");
		exit(1);
	}
	res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	res->c_floor = int_to_color(get_color_int(paths->floor));
}

void	init_look(t_game *game)
{
	game->minimap.cblue = int_to_color(get_color_int(C_BLUE));
	game->minimap.cfloor = int_to_color(get_color_int(C_FLOOR));
	game->minimap.cwall = int_to_color(get_color_int(C_WALL));
	game->minimap.cside = int_to_color(get_color_int(C_SIDE));
	game->minimap.cplayer = int_to_color(get_color_int(C_PLAYER));
	game->minimap.ctransparent.r = 0;
	game->minimap.ctransparent.g = 0;
	game->minimap.ctransparent.b = 0;
	game->minimap.ctransparent.a = 0;
}

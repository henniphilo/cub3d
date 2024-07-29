/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:51 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/26 11:41:37 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	wall_logic(t_render *render, t_minimap *minimap)
{
	t_ray	*ray;

	ray = &render->ray;
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->grid_pos_x += ray->step_x;
		render->flag_side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->grid_pos_y += ray->step_y;
		render->flag_side = 1;
	}
	if (minimap->map[ray->grid_pos_y][ray->grid_pos_x] == '1')
		render->flag_hit_wall = 1;
}

void	perform_dda(t_render *render, t_minimap *minimap)
{
	render->flag_hit_wall = 0;
	while (render->flag_hit_wall == 0)
	{
		wall_logic(render, minimap);
	}
}

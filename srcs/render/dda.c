/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:30:51 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/21 18:30:52 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	wall_logic(t_render_data *render_data, t_map_data *map_data)
{
	t_ray	*ray;

	ray = &render_data->ray;
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->grid_pos_x += ray->step_x;
		render_data->flag_side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->grid_pos_y += ray->step_y;
		render_data->flag_side = 1;
	}
	if (map_data->map[ray->grid_pos_y][ray->grid_pos_x] == '1')
		render_data->flag_hit_wall = 1;
}

static void	door_logic(t_render_data *render_data, t_map_data *map_data)
{
	t_ray	*ray;

	ray = &render_data->ray;
	if (map_data->map[ray->grid_pos_y][ray->grid_pos_x] == 'D')
	{
		if (is_door(render_data, ray->grid_pos_x, ray->grid_pos_y))
		{
			render_data->flag_hit_wall = 1;
			render_data->flag_hit_door = 1;
		}
	}
}

void	perform_dda(t_render_data *render_data, t_map_data *map_data)
{
	render_data->flag_hit_door = 0;
	render_data->flag_hit_wall = 0;
	while (render_data->flag_hit_wall == 0)
	{
		wall_logic(render_data, map_data);
		door_logic(render_data, map_data);
	}
}

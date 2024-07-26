/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:42 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:44 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_render	init_render_data(void)
{
	t_render	render;

	render.mlx_ptr = NULL;
	render.screen_image = NULL;
	render.doors = NULL;
	render.targets = NULL;
	render.screen_image = NULL;
	render.flag_hit_wall = 0;
	render.flag_hit_door = 0;
	render.flag_hit_target = 0;
	render.flag_side = 0;
	render.flag_render = 1;
	render.camera = init_camera();
	render.player = init_player();
	render.ray = init_ray();
	render.raycast = init_raycast();
	render.target_count = 0;
	render.door_count = 0;
	render.air_count = 0;
	render.count_oxy_caught = 0;
	render.count_fish_caught = 0;
	render.res = init_visuals();
	return (render);
}

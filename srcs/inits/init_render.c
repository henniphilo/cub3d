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

t_render_data	init_render_data(void)
{
	t_render_data	render_data;

	render_data.doors = NULL;
	render_data.targets = NULL;
	render_data.screen_image = NULL;
	render_data.flag_hit_wall = 0;
	render_data.flag_hit_door = 0;
	render_data.flag_hit_target = 0;
	render_data.flag_side = 0;
	render_data.flag_render = 1;
	render_data.camera = init_camera();
	render_data.player = init_player();
	render_data.ray = init_ray();
	render_data.raycast = init_raycast();
	render_data.target_count = 0;
	render_data.door_count = 0;
	render_data.air_count = 0;
	render_data.count_oxy_caught = 0;
	render_data.count_fish_caught = 0;
	return (render_data);
}

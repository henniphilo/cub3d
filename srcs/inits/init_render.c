/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:42 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:14 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_render	init_render_data(void)
{
	t_render	render;

	render.mlx_ptr = NULL;
	render.screen_image = NULL;
	render.screen_image = NULL;
	render.flag_hit_wall = 0;
	render.flag_side = 0;
	render.flag_render = 1;
	render.camera = init_camera();
	render.player = init_player();
	render.ray = init_ray();
	render.raycast = init_raycast();
	render.res = init_visuals();
	return (render);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:37 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:41 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_raycast	init_raycast(void)
{
	t_raycast	raycast;

	raycast.draw_end = 0;
	raycast.draw_start = 0;
	raycast.line_height = 0;
	raycast.perp_wall_dist = 0;
	raycast.tex_pos = 0;
	raycast.tex_step_size = 0;
	raycast.tex_step_size = 0;
	raycast.tex_x = 0;
	return (raycast);
}

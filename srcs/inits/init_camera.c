/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:11 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:15 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_camera	init_camera(void)
{
	t_camera	camera;

	camera.cameraX = 0;
	camera.plane_x = 0;
	camera.plane_y = 0;
	return (camera);
}

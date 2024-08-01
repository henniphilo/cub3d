/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:21 by vketteni          #+#    #+#             */
/*   Updated: 2024/08/01 10:31:04 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_minimap	init_map_data(void)
{
	t_minimap	map;

	map.input_table = NULL;
	map.height = 0;
	map.width = 0;
	map.map = NULL;
	map.x_axis = 0;
	map.y_axis = 0;
	map.fir_dir = 'X';
	return (map);
}

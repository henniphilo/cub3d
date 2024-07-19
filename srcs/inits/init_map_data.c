/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:21 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:24 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_map_data	init_map_data(void)
{
	t_map_data	map;

	map.input_table = NULL;
	map.height = 0;
	map.width = 0;
	map.map = NULL;
	map.x_axis = 0;
	map.y_axis = 0;
	return (map);
}

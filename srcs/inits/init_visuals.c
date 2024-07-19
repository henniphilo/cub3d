/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visuals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:47 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:48 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_visual	init_visuals(void)
{
	t_visual	visual_res;

	visual_res.door = NULL;
	visual_res.player = NULL;
	visual_res.target = NULL;
	visual_res.air = NULL;
	visual_res.ea = NULL;
	visual_res.no = NULL;
	visual_res.so = NULL;
	visual_res.we = NULL;
	visual_res.target_img = NULL;
	return (visual_res);
}

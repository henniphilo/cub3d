/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:44 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:46 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_texpaths	init_texpaths(void)
{
	t_texpaths	paths;

	paths.ceiling = NULL;
	paths.door = NULL;
	paths.target = NULL;
	paths.floor = NULL;
	paths.ea = NULL;
	paths.no = NULL;
	paths.so = NULL;
	paths.we = NULL;
	paths.air = NULL;
	paths.bubbles = NULL;
	return (paths);
}
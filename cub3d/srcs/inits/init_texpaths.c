/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texpaths_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:44 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/26 11:37:58 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_texpaths	init_texpaths(void)
{
	t_texpaths	paths;

	paths.ceiling = NULL;
	paths.floor = NULL;
	paths.ea = NULL;
	paths.no = NULL;
	paths.so = NULL;
	paths.we = NULL;
	return (paths);
}

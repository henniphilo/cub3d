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

t_ressources	init_visuals(void)
{
	t_ressources	res;

	res.door = NULL;
	res.bubbles_img = NULL;
	res.bubbles = NULL;
	res.target = NULL;
	res.air = NULL;
	res.ea = NULL;
	res.no = NULL;
	res.so = NULL;
	res.we = NULL;
	return (res);
}

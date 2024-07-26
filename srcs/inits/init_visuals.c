/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visuals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:47 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:24 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_ressources	init_visuals(void)
{
	t_ressources	res;

	res.ea = NULL;
	res.no = NULL;
	res.so = NULL;
	res.we = NULL;
	return (res);
}

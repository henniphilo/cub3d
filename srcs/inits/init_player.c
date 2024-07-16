/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:17:28 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:32 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_player	init_player(void)
{
	t_player	player;

	player.dir_x = 0;
	player.dir_y = 0;
	player.pos_x = 0;
	player.pos_y = 0;
	return (player);
}

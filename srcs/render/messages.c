/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:53:49 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/23 15:55:29 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	render_ingame_messages(t_game *game)
{
	if (game->render.count_oxy_caught == 0)
		mlx_put_string(game->render.mlx_ptr,
			" You need air! Hurry! Find the tank!", 400, 0);
	else
		print_got_air(game);
}

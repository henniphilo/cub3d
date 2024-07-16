/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:20:57 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:20:58 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	parse(t_game *game, char **argv)
{
	open_map(game, argv[1]);
	if (!game->map_data.map)
		return (1); ///TODO: handle clean exit
	return (0);
}

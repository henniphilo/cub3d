/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:20:20 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 14:20:23 by vketteni         ###   ########.fr       */
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

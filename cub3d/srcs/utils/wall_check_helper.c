/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:42 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/23 14:50:39 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static int	is_invalid(char **map, int x, int y)
{
	return (map[y][x] == ' ' || map[y][x] == '\n' || map[y][x] == '\0');
}

static int	check_neighbors(t_minimap *minimap, int x, int y)
{
	if (x > 0 && is_invalid(minimap->map, x - 1, y))
	{
		printf("Invalid neighbor at (%d, %d): map[%d][%d] = %c\n", y, x, y, x
			- 1, minimap->map[y][x - 1]);
		return (1);
	}
	if (x < minimap->x_axis[y] - 1 && is_invalid(minimap->map, x + 1, y))
	{
		printf("Invalid neighbor at (%d, %d): map[%d][%d] = %c\n", y, x, y, x
			+ 1, minimap->map[y][x + 1]);
		return (1);
	}
	if (y > 0 && is_invalid(minimap->map, x, y - 1))
	{
		printf("Invalid neighbor at (%d, %d): map[%d][%d] = %c\n", y, x, y - 1,
			x, minimap->map[y - 1][x]);
		return (1);
	}
	if (y < minimap->y_axis - 1 && is_invalid(minimap->map, x, y + 1))
	{
		printf("Invalid neighbor at (%d, %d): map[%d][%d] = %c\n", y, x, y + 1,
			x, minimap->map[y + 1][x]);
		return (1);
	}
	return (0);
}

int	check_adjacent(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->y_axis)
	{
		x = 0;
		while (x < minimap->x_axis[y] && minimap->map[y][x] != '\n')
		{
			if (minimap->map[y][x] == '0' || minimap->map[y][x] == 'L'
				|| minimap->map[y][x] == 'T' || minimap->map[y][x] == 'E'
				|| minimap->map[y][x] == 'W' || minimap->map[y][x] == 'S'
				|| minimap->map[y][x] == 'N' || minimap->map[y][x] == 'D')
			{
				if (check_neighbors(minimap, x, y) == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

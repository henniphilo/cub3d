/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:42 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/28 18:39:33 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static int	check_top(t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < minimap->x_axis[0] && minimap->map[0][i] != '\n')
	{
		while (minimap->map[0][i] == ' ')
		{
			minimap->map[0][i] = '1';
			i++;
		}
		if (minimap->map[0][i] != '1')
		{
			printf("Top border error at position (0, %d): map[0][%d] = %c\n", i,
				i, minimap->map[0][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_bottom(t_minimap *minimap)
{
	int	i;
	int	height;

	i = 0;
	height = minimap->y_axis;
	while (i < minimap->x_axis[height - 1] && minimap->map[height
			- 1][i] != '\n')
	{
		if (minimap->map[height - 1][i] != '1' && minimap->map[height
			- 1][i] != ' ')
		{
			printf("Bottom border error at position (%d, %d): map[%d][%d] ="
				"%c\n", height - 1, i, height - 1, i, minimap->map[height
				- 1][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_sides(t_minimap *minimap)
{
	int	y;

	y = 1;
	while (y < minimap->y_axis - 1 && minimap->map[y][minimap->x_axis[y]
		- 1] != '\n')
	{
		if (minimap->map[y][0] != '1' || minimap->map[y][minimap->x_axis[y]
			- 1] != '1')
		{
			printf("Left border error at position (%d, 0): map[%d][0] = %c\n",
				y, y, minimap->map[y][0]);
			printf(
				"Right border error at position (%d, %d): map[%d][%d] = %c\n",
				y, minimap->x_axis[y] - 1, y, minimap->x_axis[y]
				- 1, minimap->map[y][minimap->x_axis[y] - 1]);
			return (1);
		}
		y++;
	}
	return (0);
}

static int	check_allowed_symbols(t_minimap *minimap)
{
	int		x;
	int		y;
	char	pos;

	printf("Minimap height: %d\n", minimap->y_axis);
	y = 0;
	while (y < minimap->y_axis)
	{
		printf("Line %d width: %d\n", y, minimap->x_axis[y]);
		x = 0;
		while (x < minimap->x_axis[y] && minimap->map[y][x] != '\n')
		{
			pos = minimap->map[y][x];
			printf("Checking symbol at (%d, %d): %c\n", y, x, pos);
			if (pos != 'W' && pos != 'S' && pos != 'N' && pos != 'E'
				&& pos != '0' && pos != '1' && pos != ' ' && pos != '\n')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	walls_check(t_minimap *minimap)
{
	if (check_allowed_symbols(minimap))
	{
		printf("return in allowed sym\n");
		return (1);
	}
	if (check_adjacent(minimap))
	{
		printf("return in adjacent\n");
		return (1);
	}
	if (check_bottom(minimap))
	{
		printf("return in check bottom\n");
		return (1);
	}
	if (check_top(minimap))
	{
		printf("return in check top\n");
		return (1);
	}
	if (check_sides(minimap))
	{
		printf("return in check sides\n");
		return (1);
	}
	return (0);
}

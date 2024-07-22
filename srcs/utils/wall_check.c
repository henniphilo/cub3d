/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:42 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:18:43 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static int	check_top(t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < minimap->x_axis[0] && minimap->map[0][i] != '\n')
	{
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
			printf(
				"Bottom border error at position (%d, %d): map[%d][%d] = %c\n",
				height - 1, i, height - 1, i,
				minimap->map[height - 1][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_sides(t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < minimap->y_axis - 1 && minimap->map[j][minimap->x_axis[j]
		- 1] != '\n')
	{
		if (minimap->map[j][0] != '1' || minimap->map[j][minimap->x_axis[j]
			- 1] != '1')
		{
			printf("Left border error at position (%d, 0): map[%d][0] = %c\n",
				j, j, minimap->map[j][0]);
			printf(
				"Right border error at position (%d, %d): map[%d][%d] = %c\n",
				j, minimap->x_axis[j] - 1, j, minimap->x_axis[j] - 1,
				minimap->map[j][minimap->x_axis[j] - 1]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	walls_check(t_minimap *minimap)
{
	if (check_bottom(minimap))
		return (1);
	if (check_top(minimap))
		return (1);
	if (check_sides(minimap))
		return (1);
	return (0);
}

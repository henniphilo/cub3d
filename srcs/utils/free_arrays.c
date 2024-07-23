/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:42:50 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:18 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	free_input_table(int map_height, char **input_table)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(input_table[i]);
		i++;
	}
	free(input_table);
}

void	free_string_arr(char **string_arr)
{
	int	i;

	i = 0;
	while (string_arr[i])
	{
		free(string_arr[i]);
		i++;
	}
	free(string_arr);
}
void	free_paths(t_texpaths *paths)
{
	if (paths)
	{
		if (paths->we)
			free(paths->we);
		if (paths->so)
			free(paths->so);
		if (paths->ea)
			free(paths->ea);
		if (paths->no)
			free(paths->no);
	}
}

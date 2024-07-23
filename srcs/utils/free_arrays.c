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
	if (paths && paths->we)
		free(paths->we);
	if (paths && paths->so)
		free(paths->so);
	if (paths && paths->ea)
		free(paths->ea);
	if (paths && paths->no)
		free(paths->no);
	if (paths && paths->air)
		free(paths->no);
	if (paths && paths->bubbles)
		free(paths->bubbles);
	if (paths && paths->door)
		free(paths->door);
	if (paths && paths->air)
		free(paths->air);
	if (paths && paths->target)
		free(paths->target);
	if (paths && paths->floor)
		free(paths->floor);
	if (paths && paths->door)
		free(paths->door);
	if (paths && paths->ceiling)
		free(paths->ceiling);
}

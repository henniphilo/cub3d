/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:52 by hwiemann          #+#    #+#             */
/*   Updated: 2024/07/16 13:18:53 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	args_check(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./cube [mapfile.cub]\n");
		exit(EXIT_FAILURE);
	}
	if (check_file_ending_cub(argv[1]))
	{
		printf("Error: Input file is not .cub \n");
		terminate_game(NULL, EXIT_FAILURE);
	}
}

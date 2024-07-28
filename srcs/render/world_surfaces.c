/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_surfaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:07:31 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/16 17:20:12 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	calculate_initial_side_distances(t_render *render)
{
	if (render->ray.ray_dir_x < 0)
	{
		render->ray.step_x = -1;
		render->ray.side_dist_x = (render->player.pos_x
				- render->ray.grid_pos_x) * render->ray.delta_dist_x;
	}
	else
	{
		render->ray.step_x = 1;
		render->ray.side_dist_x = (render->ray.grid_pos_x + 1.0
				- render->player.pos_x) * render->ray.delta_dist_x;
	}
	if (render->ray.ray_dir_y < 0)
	{
		render->ray.step_y = -1;
		render->ray.side_dist_y = (render->player.pos_y
				- render->ray.grid_pos_y) * render->ray.delta_dist_y;
	}
	else
	{
		render->ray.step_y = 1;
		render->ray.side_dist_y = (render->ray.grid_pos_y + 1.0
				- render->player.pos_y) * render->ray.delta_dist_y;
	}
}

void	setup_render_params(uint32_t x, t_render *render, mlx_image_t *image)
{
	t_ray		*ray;
	t_camera	*camera;
	t_player	*player;

	ray = &render->ray;
	camera = &render->camera;
	player = &render->player;
	camera->camerax = 2 * x / (double)image->width - 1;
	ray->ray_dir_x = player->dir_x + camera->plane_x * camera->camerax;
	ray->ray_dir_y = player->dir_y + camera->plane_y * camera->camerax;
	ray->grid_pos_x = (int)player->pos_x;
	ray->grid_pos_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	render->flag_hit_wall = 0;
	calculate_initial_side_distances(render);
}

void	render_surfaces(t_game *game)
{
	t_render	*render;
	mlx_image_t	*img;
	uint32_t	x;

	img = game->render.screen_image;
	render = &game->render;
	ft_memset(img->pixels, 0, img->width * img->height * 4);
	mini_map_init(game);
	x = 0;
	while (x < img->width)
	{
		setup_render_params(x, render, img);
		perform_dda(render, &game->minimap);
		render_logic(game, x);
		x++;
	}
}

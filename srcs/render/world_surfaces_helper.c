/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_surfaces_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:28:29 by vketteni          #+#    #+#             */
/*   Updated: 2024/07/21 18:28:33 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	wall_distance_and_height(int x, t_render *render,
		mlx_image_t *image)
{
	if (render->flag_side == 0)
		render->raycast.perp_wall_dist = (render->ray.grid_pos_x
				- render->player.pos_x + (1 - render->ray.step_x) / 2)
			/ render->ray.ray_dir_x;
	else
		render->raycast.perp_wall_dist = (render->ray.grid_pos_y
				- render->player.pos_y + (1 - render->ray.step_y) / 2)
			/ render->ray.ray_dir_y;
	render->z_buffer[x] = render->raycast.perp_wall_dist;
	render->raycast.line_height = (int)(image->height
			/ render->raycast.perp_wall_dist);
	render->raycast.draw_start = -render->raycast.line_height / 2
		+ image->height / 2;
	if (render->raycast.draw_start < 0)
		render->raycast.draw_start = 0;
	render->raycast.draw_end = render->raycast.line_height / 2
		+ image->height / 2;
	if (render->raycast.draw_end >= (int)image->height)
		render->raycast.draw_end = image->height - 1;
}

static void	surface_textures(t_render *render, mlx_image_t *image,
		mlx_texture_t *tex)
{
	double	wall_x;

	if (render->flag_side == 0)
		wall_x = render->player.pos_y + render->raycast.perp_wall_dist
			* render->ray.ray_dir_y;
	else
		wall_x = render->player.pos_x + render->raycast.perp_wall_dist
			* render->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	render->raycast.tex_x = (int)(wall_x * (double)tex->width);
	if (render->flag_side == 0 && render->ray.ray_dir_x > 0)
		render->raycast.tex_x = tex->width - render->raycast.tex_x
			- 1;
	if (render->flag_side == 1 && render->ray.ray_dir_y < 0)
		render->raycast.tex_x = tex->width - render->raycast.tex_x
			- 1;
	render->raycast.tex_step_size = 1.0 * tex->height
		/ render->raycast.line_height;
	render->raycast.tex_pos = (render->raycast.draw_start
			- image->height / 2 + render->raycast.line_height / 2)
		* render->raycast.tex_step_size;
}

static mlx_texture_t	*select_texture(t_render *render)
{
	mlx_texture_t	*selected_texture;

	selected_texture = NULL;
	if (render->flag_side == 0)
	{
		if (render->ray.ray_dir_x > 0)
			selected_texture = render->res.ea;
		else
			selected_texture = render->res.we;
	}
	else
	{
		if (render->ray.ray_dir_y > 0)
			selected_texture = render->res.so;
		else
			selected_texture = render->res.no;
	}
	return (selected_texture);
}

static void	calculate_surfaces(int x, t_render *render,
		mlx_image_t *image, mlx_texture_t *tex)
{
	wall_distance_and_height(x, render, image);
	surface_textures(render, image, tex);
}

void	render_logic(t_game *game, int x)
{
	mlx_texture_t	*selected_texture;

	selected_texture = select_texture(&game->render);
	if (selected_texture != NULL)
	{
		calculate_surfaces(x, &game->render,
			game->render.screen_image, selected_texture);
		draw_line(x, game, game->render.screen_image, selected_texture);
	}
	if (game->render.flag_hit_door == 1 && is_door(&game->render,
			game->render.ray.grid_pos_x, game->render.ray.grid_pos_y))
	{
		selected_texture = game->render.res.door;
		calculate_surfaces(x, &game->render,
			game->render.screen_image, selected_texture);
		draw_line(x, game, game->render.screen_image, selected_texture);
	}
}

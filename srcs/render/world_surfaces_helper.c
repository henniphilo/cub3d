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

static void	wall_distance_and_height(int x, t_render_data *render_data,
		mlx_image_t *image)
{
	if (render_data->flag_side == 0)
		render_data->raycast.perp_wall_dist = (render_data->ray.grid_pos_x
				- render_data->player.pos_x + (1 - render_data->ray.step_x) / 2)
			/ render_data->ray.ray_dir_x;
	else
		render_data->raycast.perp_wall_dist = (render_data->ray.grid_pos_y
				- render_data->player.pos_y + (1 - render_data->ray.step_y) / 2)
			/ render_data->ray.ray_dir_y;
	render_data->z_buffer[x] = render_data->raycast.perp_wall_dist;
	render_data->raycast.line_height = (int)(image->height
			/ render_data->raycast.perp_wall_dist);
	render_data->raycast.draw_start = -render_data->raycast.line_height / 2
		+ image->height / 2;
	if (render_data->raycast.draw_start < 0)
		render_data->raycast.draw_start = 0;
	render_data->raycast.draw_end = render_data->raycast.line_height / 2
		+ image->height / 2;
	if (render_data->raycast.draw_end >= (int)image->height)
		render_data->raycast.draw_end = image->height - 1;
}

static void	surface_textures(t_render_data *render_data, mlx_image_t *image,
		mlx_texture_t *tex)
{
	double	wall_x;

	if (render_data->flag_side == 0)
		wall_x = render_data->player.pos_y + render_data->raycast.perp_wall_dist
			* render_data->ray.ray_dir_y;
	else
		wall_x = render_data->player.pos_x + render_data->raycast.perp_wall_dist
			* render_data->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	render_data->raycast.tex_x = (int)(wall_x * (double)tex->width);
	if (render_data->flag_side == 0 && render_data->ray.ray_dir_x > 0)
		render_data->raycast.tex_x = tex->width - render_data->raycast.tex_x
			- 1;
	if (render_data->flag_side == 1 && render_data->ray.ray_dir_y < 0)
		render_data->raycast.tex_x = tex->width - render_data->raycast.tex_x
			- 1;
	render_data->raycast.tex_step_size = 1.0 * tex->height
		/ render_data->raycast.line_height;
	render_data->raycast.tex_pos = (render_data->raycast.draw_start
			- image->height / 2 + render_data->raycast.line_height / 2)
		* render_data->raycast.tex_step_size;
}

static mlx_texture_t	*select_texture(t_render_data *render_data)
{
	mlx_texture_t	*selected_texture;

	selected_texture = NULL;
	if (render_data->flag_side == 0)
	{
		if (render_data->ray.ray_dir_x > 0)
			selected_texture = render_data->visual_ressources->ea;
		else
			selected_texture = render_data->visual_ressources->we;
	}
	else
	{
		if (render_data->ray.ray_dir_y > 0)
			selected_texture = render_data->visual_ressources->so;
		else
			selected_texture = render_data->visual_ressources->no;
	}
	return (selected_texture);
}

static void	calculate_surfaces(int x, t_render_data *render_data,
		mlx_image_t *image, mlx_texture_t *tex)
{
	wall_distance_and_height(x, render_data, image);
	surface_textures(render_data, image, tex);
}

void	render_logic(t_game *game, int x)
{
	mlx_texture_t	*selected_texture;

	selected_texture = select_texture(&game->render_data);
	if (selected_texture != NULL)
	{
		calculate_surfaces(x, &game->render_data,
			game->render_data.screen_image, selected_texture);
		draw_line(x, game, game->render_data.screen_image, selected_texture);
	}
	if (game->render_data.flag_hit_door == 1 && is_door(&game->render_data,
			game->render_data.ray.grid_pos_x, game->render_data.ray.grid_pos_y))
	{
		selected_texture = game->visual_res.door;
		calculate_surfaces(x, &game->render_data,
			game->render_data.screen_image, selected_texture);
		draw_line(x, game, game->render_data.screen_image, selected_texture);
	}
}

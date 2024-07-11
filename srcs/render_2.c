#include "../incl/cub3d.h"

void calculate_initial_side_distances(t_render_data* render_data) {
	t_ray		*ray;
	t_player	*player;

	ray = &render_data->ray;
	player = &render_data->player;
    if (ray->ray_dir_x < 0) {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->grid_pos_x) * ray->delta_dist_x;
    } else {
        ray->step_x = 1;
        ray->side_dist_x = (ray->grid_pos_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }

    if (ray->ray_dir_y < 0) {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->grid_pos_y) * ray->delta_dist_y;
    } else {
        ray->step_y = 1;
        ray->side_dist_y = (ray->grid_pos_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
}


void    setup_render_params(uint32_t  x, t_render_data *render_data, mlx_image_t* image)
{
	t_ray		*ray;
	t_camera	*camera;
	t_player	*player;

	ray = &render_data->ray;
	camera = &render_data->camera;
	player = &render_data->player;
    camera->cameraX = 2 * x / (double)image->width - 1;
    ray->ray_dir_x = player->dir_x + camera->plane_x * camera->cameraX;
    ray->ray_dir_y = player->dir_y + camera->plane_y * camera->cameraX;
    ray->grid_pos_x = (int)player->pos_x;
    ray->grid_pos_y = (int)player->pos_y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    render_data->flag_hit_wall = 0;
    calculate_initial_side_distances(render_data);
}

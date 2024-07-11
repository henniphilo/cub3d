#include "../incl/cub3d.h"

t_sprite *init_sprite(mlx_t *mlx, const char *path, float x, float y)
{
    t_sprite *sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
    sprite->pos_x = x;
    sprite->pos_y = y;
	
    sprite->img = mlx_texture_to_image(mlx, mlx_load_png(path));
    if (!sprite->img)
        return (NULL);
    return (sprite);
}

// void calculate_sprite_position(t_sprite *sprite, float player_x, float player_y, float dir_x, float dir_y, float plane_x, float plane_y, int screen_width, int screen_height, float *z_buffer, mlx_image_t *img)
void calculate_sprite_position(t_game *game)
{
	
	int i = 0;
	while (i < game->target_count)
	{
		double sprite_x = game->render_data.targets[i].pos_x - game->render_data.player.pos_x;
		double sprite_y = game->render_data.targets[i].pos_y - game->render_data.player.pos_y;

		double inv_det = 1.0 / (game->render_data.camera.plane_x * game->render_data.player.dir_y - game->render_data.player.dir_x * game->render_data.camera.plane_y); // required for correct matrix multiplication

		double transform_x = inv_det * (game->render_data.player.dir_y * sprite_x - game->render_data.player.dir_x * sprite_y);
		double transform_y = inv_det * (-game->render_data.camera.plane_y * sprite_x + game->render_data.camera.plane_x * sprite_y); // this is actually the depth inside the screen, that what Z is in 3D

		int sprite_screen_x = (int)((WINDOW_WIDTH / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(WINDOW_HEIGHT / transform_y)); // using 'transform_y' instead of the real distance prevents fisheye
		int draw_start_y = -sprite_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end_y >= WINDOW_HEIGHT) draw_end_y = WINDOW_HEIGHT - 1;

		int sprite_width = abs((int)(WINDOW_HEIGHT / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= WINDOW_WIDTH) draw_end_x = WINDOW_WIDTH - 1;

		// Draw the sprite
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * game->visual_res.target->width / sprite_width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < WINDOW_WIDTH && transform_y < game->render_data.z_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = (y) * 256 - WINDOW_HEIGHT * 128 + sprite_height * 128;
					int tex_y = ((d * game->visual_res.target->height) / sprite_height) / 256;
					uint32_t color = get_pixel(game->visual_res.target, tex_x, tex_y);
					if (color != 0xFF000000) // assuming 0xFF000000 is the transparency key (black)
						set_pixel(game->img, stripe, y, color);
				}
			}
		}
		i++;
	}
}

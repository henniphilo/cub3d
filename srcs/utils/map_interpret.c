#include "../../incl/cub3d.h"

// need to look int mlx_texture_t struct and calculate pixels to distance


void	load_visuals(t_game *game, t_visual *visual_res, t_texpaths *paths)
{
	(void)game;
	//printf("is getting tex\n");
	visual_res->NO = mlx_load_png(paths->NO);
	visual_res->SO = mlx_load_png(paths->SO);
	visual_res->WE = mlx_load_png(paths->WE);
	visual_res->EA = mlx_load_png(paths->EA);
	visual_res->door = mlx_load_png(paths->door);
	visual_res->target = mlx_load_png(paths->target);
	if (!(visual_res->NO) || !(visual_res->SO) || !(visual_res->WE)
		|| !(visual_res->EA) || !(visual_res->door) || !(visual_res->target))
	{
		printf("Error texture load\n");
		exit(1);
	}
	visual_res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	visual_res->c_floor = int_to_color(get_color_int(paths->floor));

}
// void	get_img(t_game *game)
// {
// 	load_visuals(game);
// 	game->image.NO = mlx_texture_to_image(game->mlx_ptr,
// 			game->visual_res.NO);
// 	game->image.SO = mlx_texture_to_image(game->mlx_ptr,
// 			game->visual_res.SO);
// 	game->image.WE = mlx_texture_to_image(game->mlx_ptr,
// 			game->visual_res.WE);
// 	game->image.EA = mlx_texture_to_image(game->mlx_ptr,
// 			game->visual_res.EA);
// 	clean_texture(game);
// }

void	clean_texture(t_game *game)
{
	//printf("in clean tex \n");
	if (game->visual_res.NO)
		mlx_delete_texture(game->visual_res.NO);
	if (game->visual_res.SO)
		mlx_delete_texture(game->visual_res.SO);
	if (game->visual_res.WE)
		mlx_delete_texture(game->visual_res.WE);
	if (game->visual_res.EA)
		mlx_delete_texture(game->visual_res.EA);
	if (game->visual_res.door)
		mlx_delete_texture(game->visual_res.door);
	if (game->visual_res.target)
		mlx_delete_texture(game->visual_res.target);
	if (game->visual_res.player)
		mlx_delete_texture(game->visual_res.player);
	// mlx_delete_texture(game->visual_res.wall);
	// mlx_delete_texture(game->visual_res.target);
}

void	clean_img(t_game *game)
{
	mlx_delete_image(game->mlx_ptr, game->img);
	// mlx_delete_image(game->mlx_ptr, game->image.SO);
	// mlx_delete_image(game->mlx_ptr, game->image.EA);
	// mlx_delete_image(game->mlx_ptr, game->image.WE);
	// mlx_delete_image(game->mlx_ptr, game->image.door);
	// mlx_delete_image(game->mlx_ptr, game->image.player);
	// mlx_delete_image(game->mlx_ptr, game->image.target);
}


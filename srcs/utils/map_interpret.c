#include "../../incl/cub3d.h"

void	load_visuals(t_visual *visual_res, t_texpaths *paths)
{
	if (paths->NO)
		visual_res->NO = mlx_load_png(paths->NO);
	else
		printf("North texture missing\n");
	if (paths->SO)
		visual_res->SO = mlx_load_png(paths->SO);
	else
		printf("SO texture missing\n");
	if (paths->WE)
		visual_res->WE = mlx_load_png(paths->WE);
	else
		printf("WE texture missing\n");
	if (paths->EA)
		visual_res->EA = mlx_load_png(paths->EA);
	else
		printf("EA texture missing\n");
	if (paths->door)
		visual_res->door = mlx_load_png(paths->door);
	else
		printf("door texture missing\n");
	if (paths->target)
		visual_res->target = mlx_load_png(paths->target);
	else
		printf("target texture missing\n");
	if (paths->air)
		visual_res->air = mlx_load_png(paths->air);
	else
		printf("air texture missing\n");
	if (paths->bubbles)
		visual_res->bubbles = mlx_load_png(paths->target);
	else
		printf("bubbles texture missing\n");
	// if (!(visual_res->NO) || !(visual_res->SO) || !(visual_res->WE)
	// 	|| !(visual_res->EA) || !(visual_res->door) || !(visual_res->target) || !(visual_res->air))
	// {
	// 	printf("Error texture load\n");
	// 	exit(1);
	// }
	visual_res->c_ceiling = int_to_color(get_color_int(paths->ceiling));
	visual_res->c_floor = int_to_color(get_color_int(paths->floor));

}

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
	mlx_delete_image(game->mlx_ptr, game->visual_res.bubbles_img);
}


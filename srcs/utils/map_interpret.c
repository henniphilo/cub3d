#include "../../incl/cub3d.h"

// need to look int mlx_texture_t struct and calculate pixels to distance


void	get_textures(t_game *game)
{
	//printf("is getting tex\n");
	game->tex.NO = mlx_load_png(game->look.NO);
	game->tex.SO = mlx_load_png(game->look.SO);
	game->tex.WE = mlx_load_png(game->look.WE);
	game->tex.EA = mlx_load_png(game->look.EA);
	game->tex.door = mlx_load_png(game->look.door);
	game->tex.target = mlx_load_png(game->look.target);
	if (!(game->tex.NO) || !(game->tex.SO) || !(game->tex.WE)
		|| !(game->tex.EA) || !(game->tex.door) || !(game->tex.target))
	{
		printf("Error texture load\n");
		exit(1);
	}
}


// void	get_img(t_game *game)
// {
// 	get_textures(game);
// 	game->image.NO = mlx_texture_to_image(game->mlx_ptr,
// 			game->tex.NO);
// 	game->image.SO = mlx_texture_to_image(game->mlx_ptr,
// 			game->tex.SO);
// 	game->image.WE = mlx_texture_to_image(game->mlx_ptr,
// 			game->tex.WE);
// 	game->image.EA = mlx_texture_to_image(game->mlx_ptr,
// 			game->tex.EA);
// 	clean_texture(game);
// }

void	clean_texture(t_game *game)
{
	//printf("in clean tex \n");
	mlx_delete_texture(game->tex.NO);
	mlx_delete_texture(game->tex.SO);
	mlx_delete_texture(game->tex.WE);
	mlx_delete_texture(game->tex.EA);
	mlx_delete_texture(game->tex.door);
	mlx_delete_texture(game->tex.target);
	// mlx_delete_texture(game->tex.wall);
	// mlx_delete_texture(game->tex.player);
	// mlx_delete_texture(game->tex.target);
}

void	clean_img(t_game *game)
{
	mlx_delete_image(game->mlx_ptr, game->image.NO);
	mlx_delete_image(game->mlx_ptr, game->image.SO);
	mlx_delete_image(game->mlx_ptr, game->image.EA);
	mlx_delete_image(game->mlx_ptr, game->image.WE);
	mlx_delete_image(game->mlx_ptr, game->image.door);
	mlx_delete_image(game->mlx_ptr, game->image.player);
	mlx_delete_image(game->mlx_ptr, game->image.target);
}


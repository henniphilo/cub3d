#include "../../incl/cub3d.h"

void	get_textures(t_game *game)
{
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

void	clean_texture(t_game *game)
{
	mlx_delete_texture(game->tex.NO);
	mlx_delete_texture(game->tex.SO);
	mlx_delete_texture(game->tex.WE);
	mlx_delete_texture(game->tex.EA);
	mlx_delete_texture(game->tex.door);
	mlx_delete_texture(game->tex.target);
}

void	clean_img(t_game *game)
{
	mlx_delete_image(game->mlx_ptr, game->image.bubbles);
}


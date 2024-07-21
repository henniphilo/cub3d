#include "../../incl/cub3d.h"

void	render_ingame_messages(t_game *game)
{
	if (game->render_data.count_oxy_caught == 0)
		mlx_put_string(game->mlx_ptr,
			" You need air! Hurry! Find the tank!", 400, 0);
	else
		print_got_air(game);
	if (game->render_data.count_fish_caught != 0)
	{
		mlx_put_string(game->mlx_ptr, " You caught fish: ", 700, 0);
		mlx_put_string(game->mlx_ptr,
			ft_itoa(game->render_data.count_fish_caught), 800, 0);
	}
}
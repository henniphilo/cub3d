#include "../incl/cub3d.h"

void	set_north(t_game *game)
{
	game->render_data.player.dir_x = 0.0;
	game->render_data.player.dir_y = -1.0;
	game->render_data.camera.plane_x = 0.66;
	game->render_data.camera.plane_y = 0;
	game->map_data.first_dir = 'N';
}
void	set_south(t_game *game)
{
	game->render_data.player.dir_x = 0.0;
	game->render_data.player.dir_y = 1.0;
	game->render_data.camera.plane_x = -0.66;
	game->render_data.camera.plane_y = 0;
	game->map_data.first_dir = 'S';
}
void	set_east(t_game *game)
{
	game->render_data.player.dir_x = 1.0;
	game->render_data.player.dir_y = 0.0;
	game->render_data.camera.plane_x = 0;
	game->render_data.camera.plane_y = 0.66;
	game->map_data.first_dir = 'E';
}
void	set_west(t_game *game)
{
	game->render_data.player.dir_x = -1.0;
	game->render_data.player.dir_y = 0.0;
	game->render_data.camera.plane_x = 0;
	game->render_data.camera.plane_y = -0.66;
	game->map_data.first_dir = 'W';
}

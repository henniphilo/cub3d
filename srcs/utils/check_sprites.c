#include "../../incl/cub3d.h"

void	check_sprites(t_game *game, t_render_data *render_data, int sprite_type)
{
	t_sprite	*sprite_array;
	int			sprite_count;
	int			i;

	if (sprite_type == 0) // Checking door sprites
	{
		sprite_array = render_data->doors;
		sprite_count = game->render_data.door_count;
	}
	if (sprite_type == 2) // Checking air sprites
	{
		sprite_array = render_data->air;
		sprite_count = game->render_data.air_count;
	}
	else // Checking target sprites
	{
		sprite_array = render_data->targets;
		sprite_count = game->render_data.target_count;
	}
	i = 0;
	while (i < sprite_count)
	{
		switch (sprite_type)
		{
		case 0: // Example case for doors
			if (sprite_array[i].active)
				printf("Door at (%.2f, %.2f) is closed\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Door at (%.2f, %.2f) is open\n", sprite_array[i].pos_x,
					sprite_array[i].pos_y);
			break ;
		case 1: // Example case for targets
			if (sprite_array[i].active)
				printf("Target at (%.2f, %.2f) is not acquired\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Target at (%.2f, %.2f) is acquired\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			break ;
		case 2: // Example case for targets
			if (sprite_array[i].active)
				printf("Air at (%.2f, %.2f) is not caught\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y);
			else
				printf("Air at (%.2f, %.2f) is caught, you have %d tanks\n",
					sprite_array[i].pos_x, sprite_array[i].pos_y,
					game->render_data.count_oxy_caught);
			break ;
		// Add other cases as needed for different sprite types
		default:
			printf("Unknown sprite type at (%.2f, %.2f)\n",
				sprite_array[i].pos_x, sprite_array[i].pos_y);
			break ;
		}
		i++;
	}
}

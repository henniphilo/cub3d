#include "../incl/cub3d.h"

void	args_check(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Usage: ./cube [mapfile.cub]");
		exit(EXIT_FAILURE);
	}
	if (!check_file_ending_cub(argv[1]))
		return (terminate_game(NULL, EXIT_FAILURE));
}
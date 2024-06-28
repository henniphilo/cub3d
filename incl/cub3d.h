#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
//# include "MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // write, access, fork, execve, dup2, pipe, etc.
# include <errno.h>      // perror, strerror
# include <stdlib.h>     // getenv
# include <stddef.h>	 // Null
# include <math.h>

/* Map Parsing */
int		check_map_cub(char *file);
int		walls_check(t_game *game);
int		cub_input(t_game *game);
char	*get_path(char *line, const char *direction);
void	open_map(t_game *game, char *file);
void	space_map(t_game *game, int fd);
void	get_map(t_game *game, int fd);
void	print_map(t_game *game);
int		map_input_check(t_game *game);
void	free_data(t_game *game);





# endif

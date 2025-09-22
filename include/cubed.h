/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:21:50 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 19:31:34 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
// # include "mlx.h"
# include "libft.h"

# define ERROR 1
# define SUCCESS 0

# define WIDTH 1920
# define HEIGHT 1080

# define ERR_MAL "Memory allocation failed"
# define ERR_INVVALID_MAP "The map is or wrong or incomplete"
# define ERR_FILE_CUB "File must be a .cub file: filename.cub"
# define ERR_FILE "Error accessing file"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_MORE_PLAYERS "To many players on map"
# define ERR_NO_PLAYER "No player was found on map"
# define ERR_POS_PLAYER "Invalid position of player"
# define ERR_USE "Error usage! Expected: ./cub3d filename.cub"
# define ERR_MLX "Could not start mlx"
# define ERR_WIN "Could not create mlx window"
# define ERR_IMG "Could not create mlx image"

typedef enum e_compas
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_compas;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*image;
}	t_mlx;

typedef struct s_data
{
    char    	**map;
    int     	cords_p[2];
    t_compas	compas;
}	t_data;

typedef struct s_cubed
{
	t_data	data;
	t_mlx	mlx;
}   t_cubed;

// Initializing functions
int		is_player(char c);
int		check_surround(char **map, int y, int x, int h, int w);
int		validate_map(t_cubed *cubed, int h, int w);
int		parse_map(t_cubed *cubed, char *str);
int		init_cubed(t_cubed *cubed, char *file);
char	*read_file(const char *path);

// Cleaning and Errors
void	err_msg(char *error);

#endif
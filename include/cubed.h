/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:21:50 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:54:04 by pdaskalo         ###   ########.fr       */
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
# include <sys/time.h>
# include "mlx.h"
# include "libft.h"

# define ERROR 1
# define SUCCESS 0

# define WIDTH 960
# define HEIGHT 540

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
	void		*mlx;
	void		*win;
	void		*img;
	char		*adr;
	int			endian;
	int			bpp;
	int			size_line;
}	t_mlx;

typedef struct s_player
{
	float	x;
	float	y;
	float	r;
	int		c;
}	t_player;

typedef struct s_data
{
    char    	**map;
    int     	cords_p[2];
    t_compas	compas;
}	t_data;

typedef struct	s_rect
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
} t_rect;

typedef struct s_cubed
{
	t_player	p;
	t_data		data;
	t_mlx		mlx;
	int			keys[300];
	long		last_time;
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
void	free_cubed(t_cubed *cubed);

/* Program */
// Main program
int		process(t_cubed *cubed);

// Draw
void	draw_player(t_cubed *cubed, t_player p, int cell);
void	draw_cell(t_cubed *cubed, int x, int y, int size, int color);
int		make_minimap(t_cubed *cubed);
int		render_next_frame(t_cubed *cubed);

// Player
int		can_move(t_cubed *cubed, float nx, float ny);
void	update_player(t_cubed *cubed);
int		is_in(float x, float y, t_player p);

// Keys
int		close_window(void *param);
int		key_press(int key, t_cubed *cubed);
int		key_release(int key, t_cubed *cubed);

// Utils
int		get_map_width(char **map);
int		get_cell_size(t_cubed *cubed, int *w, int *h);
long	get_time_ms(void);
void	my_mlx_pixel_put(t_cubed *cubed, int x, int y, int color);



#endif
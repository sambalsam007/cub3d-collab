/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:21:50 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/23 22:13:36 by pdaskalo         ###   ########.fr       */
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
# include <math.h>
# include "mlx.h"
# include "libft.h"

# ifdef __APPLE__
// macOS keycodes
#  define KEY_ESC 53
#  define KEY_W   13
#  define KEY_A   0
#  define KEY_S   1
#  define KEY_D   2
# endif

# ifdef __linux__
// Linux (X11) keycodes
#  include <X11/X.h>
#  include <X11/Xlib.h>
#  include <X11/keysym.h>
#  define KEY_ESC 65307
#  define KEY_W   119
#  define KEY_A   97
#  define KEY_S   115
#  define KEY_D   100
# endif

# define ERROR 1
# define SUCCESS 0

# define WIDTH 960
# define HEIGHT 540
# define MOVE_SPEED 3.0f
# define ROT_SPEED 0.05f
# define TILE_SIZE 64
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define ERR_MAL "Memory allocation failed"
# define ERR_INV_MAP "The map is or wrong or incomplete"
# define ERR_FILE_CUB "File must be a .cub file: filename.cub"
# define ERR_FILE "Error accessing file"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_INV_FILE "Invalid data in file"
# define ERR_MORE_PLAYERS "To many players on map"
# define ERR_NO_PLAYER "No player was found on map"
# define ERR_POS_PLAYER "Invalid position of player"
# define ERR_USE "Error usage! Expected: ./cub3d filename.cub"
# define ERR_MLX "Could not start mlx"
# define ERR_WIN "Could not create mlx window"
# define ERR_IMG "Could not create mlx image"

typedef enum e_compas
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
}	t_compas;

typedef enum e_rgb
{
	RED = 0,
	GREEN = 1,
	BLUE = 2
}	t_rgb;

typedef struct s_ray
{
    float	angle;
    float	distance;
    int		hit_x;
    int		hit_y;
	int		side;
	double 	wall_t;
	double 	wall_b;
	int		wall_x;
	int		wall_y;
}   t_ray;

typedef struct s_tex
{
	void	*img;
	char	*adr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	int		found;
}	t_tex;

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

typedef struct s_minimap
{
    int     width;
    int     height;
    int     scale;
    int     first_x;
    int     first_y;
    int     last_x;
    int     last_y;
}   t_minimap;

typedef struct s_player
{
	float	fov;
	float	x;
	float	y;
	float	r;
	float	angle;
	int		c;
}	t_player;

typedef struct s_data
{
    char    	**map;
    int     	cords_p[2];
	int			color_c;
	int			color_f;
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
	t_tex		texture[4];
	t_ray		ray;
    t_minimap	minimap;
	int			keys[300];
	long		last_time;
}   t_cubed;

// Initializing functions
int		is_player(char c);
int		check_surround(char **map, int y, int x, int h);
int		validate_map(t_cubed *cubed, int h, int w);
int		parse_map(t_cubed *cubed, char **lines);
int		init_cubed(t_cubed *cubed, char *file);
void	init(t_cubed *cubed);
void	init_player(t_cubed *cubed);
char	*read_file(const char *path);
int		parse_rgb(char *s);
void	load_texture(t_cubed *cubed, t_compas dir, char *path);
int		parse_header_line(t_cubed *cubed, char *line);

// Cleaning and Errors
void	err_msg(char *error);
void	free_mlx(t_cubed *cubed);
void	free_all(t_cubed *cubed);

/* Program */
// Main program
int		process(t_cubed *cubed);
int		render_next_frame(t_cubed *cubed);

// Draw
void	draw_player(t_cubed *cubed, t_player p, int cell);
void	draw_cell(t_cubed *cubed, int x, int y, int size, int color);
// int		make_minimap(t_cubed *cubed);
void	draw_minimap(t_cubed *cubed);
void	reset_background(t_cubed *cubed);


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
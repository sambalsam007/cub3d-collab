/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:21:50 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/24 12:41:13 by pdaskalo         ###   ########.fr       */
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
# include "../mlxlib/mlx.h"
# include "../libft/libft.h"

// Linux (X11) keycodes
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# define KEY_ESC 65307
# define KEY_W   119
# define KEY_A   97
# define KEY_S   115
# define KEY_D   100
// samuel edit 09.25
# define KEY_J   65361 // TODO
# define KEY_K   65363 // TODO

# define ERROR 1
# define SUCCESS 0

# define WIDTH 800
# define HEIGHT 600

// make this modular?
// # define MAP_W 10
// # define MAP_H 10

// for wolf test
# define MOVE_SPEED 0.04    // reduced because units are tiles now

// rotation speed
# define ROT_SPEED 0.04      // increased (no need for tiny radians anymore)

// # define MOVE_SPEED 3.0f
// // samuel edit 09.25
// // change rotation speed 0.05 -> 0.005
// # define ROT_SPEED 0.05f
// samuel edit
# define TILE_SIZE 64
// # define TILE_SIZE 2
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

typedef struct s_player_ray
{
	float	ray_x;
	float	ray_y;
	float	step;
	int		map_x;
	int		map_y;
	int		minimap_x0;
	int		minimap_y0;
	int		minimap_x1;
	int		minimap_y1;
}		t_player_ray;

typedef struct s_ray
{
	float	angle;
	float	distance;
	int	hit_x;
	int	hit_y;
	// int		side;
	double 	wall_t;
	double 	wall_b;
	int		tex_x;
	int		tex_y;
	// samuel edit
	double	ray_dir_x;
	double	ray_dir_y;
	int	map_x;
	int	map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int	step_x;
	int	step_y;
	int	hit;
	int	side;
	double	perp_wall_dist;
	int	line_height;
	int	draw_start;
	int	draw_end;
	double	wall_x;
	t_compas	tex_num;
	int	tex_w;
	int	tex_h;
	int	tex_bpp;
	int	tex_line;
	char	*tex_addr;
	int	texture_x;
	double	step;
	double	tex_pos;
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
	// int		width;
	// int		height;
	// int		scale;
	// int		first_x;
	// int		first_y;
	// int		last_x;
	// int		last_y;
	// samuel edit
	int		x;
	int		y;
	int		cell;
	int		color;
	int		scale;
	int		offset_x;
	int		offset_y;
	int		map_width;
	int		map_height;
}   t_minimap;

typedef struct s_player
{
	float	fov;
	// samuel edit
	// float	x;
	// float	y;
	double	x; // is tile coordinates, NOT pixel coordinates
	double	y;
	float	r;
	float	angle;
	int		c;
	// samuel edit
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_set_player
{
	int	x;
	int	y;
}	t_set_player;

typedef struct s_data
{
	t_compas	compas;
	char **map;
	int map_h;
	int map_w;
		int	cords_p[2];
		int	color_c;
	int		color_f;
}	t_data;

typedef struct s_rect
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
}	t_rect;

typedef struct s_cubed
{
	t_player	p;
	t_data		data;
	t_mlx		mlx;
	t_tex		texture[4];
	t_ray		ray;
	t_minimap	minimap;
	int			keys[99999];
	long		last_time;
}	t_cubed;

// samuel edit 09.25
// prototypes
int		draw_minimap(t_cubed *cubed);
// samuel edit
void	draw_player(t_cubed *cubed, t_player p, t_minimap m);
int		render_next_frame(t_cubed *cubed);

// movement prototypes
void	player_forward_backward(t_cubed *cubed);
void	player_strafe_left_right(t_cubed *cubed);
void	player_rotate_left(t_cubed *c);
void	player_rotate_right(t_cubed *c);

// raycasting prototypes
void	general_calculations(t_cubed *cubed, t_ray *ray, int current_ray_nbr);

void	calc_ray_dir(t_cubed *c, t_ray *r, int current_ray_nbr);
void	set_map_xy(t_cubed *c, t_ray *r);
void	calc_delta_dist(t_ray *r);
void	calc_side_dist(t_cubed *c, t_ray *r);
void	check_for_hit(t_cubed *c, t_ray *r);
void	calc_perpendicular_wall_dist(t_cubed *c, t_ray *r);
void	calc_line_height(t_ray *r);
void	calc_draw_start_end(t_ray *r);

// texture prototypes
void	texture_calculations(t_cubed *cubed, t_ray *ray, int current_ray_nbr);
void	define_texture_compass(t_ray *r);
void	calc_hit_position_on_wall(t_cubed *c, t_ray *r);
void	find_x_coord_on_texture(t_cubed *c, t_ray *r);
void	calc_tex_x(t_ray *r);
void	calc_step(t_ray *r);
void	calc_tex_pos(t_ray *r);
void	draw_vertical_column(t_cubed *c, t_ray *r, int current_ray_nbr);

// direction ray prototypes
void	draw_player_ray(t_cubed *cubed, t_player p, t_minimap m);
void	super_nice_loop(t_cubed *c, t_player_ray *pr, \
		t_minimap *m, t_player *p);

// rendering prototypes
void	put_pixel(t_cubed *cubed, int x, int y, int color);

// Initializing functions
int		is_player(char c);
int		check_surround(char **map, int y, int x, int h);
int		validate_map(t_cubed *cubed, int h, int w);
int		parse_map(t_cubed *cubed, char **lines);
int		set_player(t_cubed *cubed, char c, t_set_player sp, int *found);

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

// Draw
void	draw_cell(t_cubed *cubed, int x, int y, t_minimap *m);
// int		make_minimap(t_cubed *cubed);
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

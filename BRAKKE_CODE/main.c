/*
e- steps to build the raycaster (minimap)
	setup minilibx window w/ esc etc
	draw a player dot
	create grid on map (chatgpt forgot draw to img -> to window)
	draw player
	make player dot move l/r/u/d
	make player rotate < >
	launch ray from player
	put walls on map
	make ray stop on walls vertical
	make ray stop on walls horizontal
	print out length of ray

	[x] draw player
	[x] make player dot move l/r/u/d
	[x] hold key to move
	[x] make it move slower
	[x] launch ray from player
	[ ] make player rotate < >
		[x] throw in chatgpt to catch errs
	[x] put walls on map
	[x] make ray stop on walls vertical
	[x] make ray stop on walls horizontal
	[x] print out length of ray
*/



#include "../mlxlib/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN_W 1000
#define WIN_H 800
#define TILE 40
#define MAP_W 10
#define MAP_H 10
#define MOVE_SPEED 2.0
#define ROT_SPEED 0.05

#define FOV (M_PI / 3)  // 60 degrees
#define STRIP_WIDTH 1
#define WALL_COLOR 0x8888FF

typedef struct s_img {
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_img;

typedef struct s_player {
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_img   img;
    t_player player;
    int     keys[256];
} t_game;

// Simple map
int world_map[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

// ===== Utility =====
void put_pixel(t_img *img, int x, int y, int color) {
    if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H) return;
    char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void clear_img(t_img *img) {
    for (int y = 0; y < WIN_H; y++)
        for (int x = 0; x < WIN_W; x++)
            put_pixel(img, x, y, 0x000000);
}

// ===== DDA raycasting =====
double cast_ray(t_game *g, double angle)
{
    double rayX = g->player.x;
    double rayY = g->player.y;

    double dx = cos(angle);
    double dy = sin(angle);

    while (1) {
        rayX += dx;
        rayY += dy;

        int mapX = (int)(rayX / TILE);
        int mapY = (int)(rayY / TILE);

        if (mapX < 0 || mapY < 0 || mapX >= MAP_W || mapY >= MAP_H)
            break;
        if (world_map[mapY][mapX] == 1)
            break;
    }

    double deltaX = rayX - g->player.x;
    double deltaY = rayY - g->player.y;
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

void draw_rays_on_map(t_game *g)
{
    int num_rays = 60; // number of rays for mini-map
    double start_angle = g->player.angle - (FOV / 2);
    double angle_step = FOV / num_rays;

    for (int i = 0; i < num_rays; i++) {
        double ray_angle = start_angle + i * angle_step;
        double length = cast_ray(g, ray_angle);

        // start position (player)
        double x0 = g->player.x / 4;
        double y0 = g->player.y / 4;

        // end position (ray hit)
        double x1 = x0 + (cos(ray_angle) * length / 4);
        double y1 = y0 + (sin(ray_angle) * length / 4);

        // simple line draw using Bresenham-like approach
        double dx = fabs(x1 - x0);
        double dy = fabs(y1 - y0);
        int steps = (dx > dy) ? dx : dy;
        double x_inc = (x1 - x0) / steps;
        double y_inc = (y1 - y0) / steps;
        double x = x0, y = y0;
        for (int j = 0; j <= steps; j++) {
            put_pixel(&g->img, (int)x, (int)y, 0x00FF00);
            x += x_inc;
            y += y_inc;
        }
    }
}


// ===== Drawing 3D walls =====
void render_3d(t_game *g)
{
    int num_rays = WIN_W / STRIP_WIDTH;
    double start_angle = g->player.angle - (FOV / 2);
    double angle_step = FOV / num_rays;

    for (int i = 0; i < num_rays; i++) {
        double ray_angle = start_angle + i * angle_step;
        double length = cast_ray(g, ray_angle);
        double corrected = length * cos(ray_angle - g->player.angle); // fish-eye correction
        double wall_height = (TILE * WIN_H) / corrected;

        int wall_top = (WIN_H / 2) - (wall_height / 2);
        int wall_bottom = (WIN_H / 2) + (wall_height / 2);

        for (int y = wall_top; y < wall_bottom; y++)
            for (int x = i * STRIP_WIDTH; x < (i+1) * STRIP_WIDTH; x++)
                put_pixel(&g->img, x, y, WALL_COLOR);
    }
}

// ===== Optional minimap =====
void draw_map(t_game *g) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            int color = (world_map[y][x] == 1) ? 0xAAAAAA : 0x000000;
            for (int i = 0; i < TILE / 4; i++)
                for (int j = 0; j < TILE / 4; j++)
                    put_pixel(&g->img, x*(TILE/4)+j, y*(TILE/4)+i, color);
        }
    }
}

void draw_player(t_game *g) {
    int px = (int)(g->player.x / 4);
    int py = (int)(g->player.y / 4);
    for (int i = -2; i <= 2; i++)
        for (int j = -2; j <= 2; j++)
            put_pixel(&g->img, px+j, py+i, 0xFF0000);
}

// ===== Rendering =====



void render(t_game *g) {
    clear_img(&g->img);
    render_3d(g);
    draw_map(g);
    draw_rays_on_map(g); // <--- new: rays on mini-map
    draw_player(g);
    mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}




// ===== Input =====
int key_press(int keycode, t_game *g) {
    if (keycode == 65307) exit(0);
    if (keycode >=0 && keycode < 256) g->keys[keycode] = 1;
    return 0;
}

int key_release(int keycode, t_game *g) {
    if (keycode >=0 && keycode < 256) g->keys[keycode] = 0;
    return 0;
}

// ===== Game loop =====
int game_loop(t_game *g) {
    double new_x = g->player.x;
    double new_y = g->player.y;

    // Move
    if (g->keys['w']) new_x += cos(g->player.angle) * MOVE_SPEED,
                      new_y += sin(g->player.angle) * MOVE_SPEED;
    if (g->keys['s']) new_x -= cos(g->player.angle) * MOVE_SPEED,
                      new_y -= sin(g->player.angle) * MOVE_SPEED;
    if (g->keys['a']) new_x += cos(g->player.angle - M_PI/2) * MOVE_SPEED,
                      new_y += sin(g->player.angle - M_PI/2) * MOVE_SPEED;
    if (g->keys['d']) new_x += cos(g->player.angle + M_PI/2) * MOVE_SPEED,
                      new_y += sin(g->player.angle + M_PI/2) * MOVE_SPEED;

    // Rotate
    if (g->keys['j']) g->player.angle -= ROT_SPEED;
    if (g->keys['k']) g->player.angle += ROT_SPEED;

    // Collision
    int mapX = (int)(new_x / TILE);
    int mapY = (int)(new_y / TILE);
    if (mapX >= 0 && mapY >= 0 && mapX < MAP_W && mapY < MAP_H &&
        world_map[mapY][mapX] == 0) {
        g->player.x = new_x;
        g->player.y = new_y;
    }

    render(g);
    return 0;
}

int handle_close(void *param) { (void)param; exit(0); return 0; }

// ===== Main =====
int main(void) {
    t_game g;
    for (int i = 0; i < 256; i++) g.keys[i] = 0;

    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, WIN_W, WIN_H, "cub3d 3D");

    g.img.img = mlx_new_image(g.mlx, WIN_W, WIN_H);
    g.img.addr = mlx_get_data_addr(g.img.img, &g.img.bpp,
                                   &g.img.line_len, &g.img.endian);

    g.player.x = 2.5 * TILE;
    g.player.y = 2.5 * TILE;
    g.player.angle = 0;

    mlx_hook(g.win, 2, 1L<<0, key_press, &g);
    mlx_hook(g.win, 3, 1L<<1, key_release, &g);
    mlx_hook(g.win, 17, 0, handle_close, &g);
    mlx_loop_hook(g.mlx, game_loop, &g);
    mlx_loop(g.mlx);

    return 0;

}






/*
GOAL: make the 3d thing
 i think  : 1hour (x4 => 4 hours of work???)
 i will vibe it 💕 step by step
 - create multiple rays.
 - store all the ray lenghts in an array (that corresponds to all pixels horizontally)
 - then we render an image based on the different ray lengths (bigger ray = smaller wall/vertical line)
 forgot -> do stuff to avoid fish-eye [perpendicular distance]
 forgot -> DDA (grid stepping) is this not in the minimap?
 - how do we rotate the player? same as in minimap, 
 	u get different ray lengths for each pixel which will create a different view.
	nothing difficult
 - moving the player, same story, shouldn't be too hard.

[x] replace pixel stepping w/ DDA stepping
[x] create multiple rays
[x] store ray lengths in array
[x] do calculations to avoid fish eye
[x] render image




*/


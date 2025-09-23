/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:48:32 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:55:45 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void put_pixel(t_cubed *cubed, int x, int y, int color, int map_w, int map_h)
{
	if (x < 0 || y < 0 || x >= map_w || y >= map_h)
		return;
	char *dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

/* REPLACED BY DDA
// samuel
// new 
// this walks pixel/pixel, small increments
// TODO: make it DDA algo, smart steps
void draw_ray(t_cubed *cubed, t_player p, int cell)
{
    // ---- don't overwrite player's angle! ----
    // p.angle = 0;   // remove this — it was forcing angle to 0

    // convert player position in tiles -> pixels
    double rayX = p.x * cell;
    double rayY = p.y * cell;

    // direction vector (unit)
    double dx = cos(p.angle);
    double dy = sin(p.angle);

    // step length in pixels per iteration (tune for quality / perf)
    const double step = 1.0; // 1 pixel per loop; try 0.5 for smoother, 2.0 for faster

    // --- compute map dimensions safely (in tiles) ---
    int map_height_tiles = 0;
    while (cubed->data.map[map_height_tiles])
        map_height_tiles++;

    int map_width_tiles = 0;
    if (map_height_tiles > 0)
    {
        // best to use the length of the longest row in case rows differ
        for (int r = 0; r < map_height_tiles; r++)
        {
            int len = (int)strlen(cubed->data.map[r]);
            if (len > map_width_tiles)
                map_width_tiles = len;
        }
    }
    // ///////////// --- compute map dimensions safely (in tiles) ---

    // convert map size to pixels for pixel-bound checks / put_pixel
    int map_width_pixels = map_width_tiles * cell;
    int map_height_pixels = map_height_tiles * cell;

    int max_steps = 2000; // max pixel steps guard

    for (int i = 0; i < max_steps; i++)
    {
        // compute which tile we're in
        int mapX = (int)(rayX / cell);
        int mapY = (int)(rayY / cell);

        // out-of-bounds -> stop
        if (mapX < 0 || mapY < 0 || mapX >= map_width_tiles || mapY >= map_height_tiles)
            break;

        // note: map stores chars like '1' and '0' — compare chars
        if (cubed->data.map[mapY][mapX] == '1')
        {
            // optional: draw the wall hit pixel in a different color
            put_pixel(cubed, (int)rayX, (int)rayY, 0xFF0000, map_width_pixels, map_height_pixels);
            break;
        }

        // draw ray pixel (green)
        put_pixel(cubed, (int)rayX, (int)rayY, 0x000000, map_width_pixels, map_height_pixels);

        // advance in pixel space
        rayX += dx * step;
        rayY += dy * step;
    }
}
*/




// replace your cast_ray() + draw_ray_line() with this

#include <math.h>

double cast_ray(t_cubed *cubed, double angle, int cell)
{
    // map dims (tiles)
    int map_h = 0;
    while (cubed->data.map[map_h])
        map_h++;
    int map_w = 0;
    for (int r = 0; r < map_h; r++)
    {
        int len = (int)strlen(cubed->data.map[r]);
        if (len > map_w) map_w = len;
    }

    // player position in tiles (not pixels)
    double posX = cubed->p.x;
    double posY = cubed->p.y;

    // ray direction (per tile)
    double rayDirX = cos(angle);
    double rayDirY = sin(angle);

    // which box of the map we're in
    int mapX = (int)posX;
    int mapY = (int)posY;

    // length of ray from one x or y-side to next x or y-side
    // guard against zero:
    double deltaDistX = (fabs(rayDirX) > 1e-9) ? fabs(1.0 / rayDirX) : 1e9;
    double deltaDistY = (fabs(rayDirY) > 1e-9) ? fabs(1.0 / rayDirY) : 1e9;

    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;
    int side = 0; // 0 = x-side hit, 1 = y-side hit

    // DDA loop
    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        // bounds check
        if (mapX < 0 || mapY < 0 || mapX >= map_w || mapY >= map_h)
            break;

        // map stores chars like '1'/'0'
        if (cubed->data.map[mapY][mapX] == '1')
            hit = 1;
    }

    // compute perpendicular distance (in tiles), robust formula
    double perpDistTiles;
    if (side == 0)
        perpDistTiles = (mapX - posX + (1 - stepX) / 2.0) / ( (fabs(rayDirX) > 1e-9) ? rayDirX : 1e-9 );
    else
        perpDistTiles = (mapY - posY + (1 - stepY) / 2.0) / ( (fabs(rayDirY) > 1e-9) ? rayDirY : 1e-9 );

    // convert to absolute and to pixels
    double perpDistPixels = fabs(perpDistTiles) * cell;
    return perpDistPixels;
}

void draw_ray_line(t_cubed *cubed, double angle, int cell)
{
    // compute map dimensions for put_pixel bounds
    int map_h = 0;
    while (cubed->data.map[map_h])
        map_h++;
    int map_w = 0;
    for (int r = 0; r < map_h; r++)
    {
        int len = (int)strlen(cubed->data.map[r]);
        if (len > map_w) map_w = len;
    }
    int map_w_px = map_w * cell;
    int map_h_px = map_h * cell;

    double dist_px = cast_ray(cubed, angle, cell);

    double startX = cubed->p.x * cell;
    double startY = cubed->p.y * cell;
    double dx = cos(angle);
    double dy = sin(angle);

    int steps = (int)(dist_px); // step per pixel
    if (steps < 0) steps = 0;

    for (int i = 0; i <= steps; i++)
    {
        int x = (int)round(startX + dx * i);
        int y = (int)round(startY + dy * i);
        put_pixel(cubed, x, y, 0x000000, map_w_px, map_h_px);
    }

    // mark hit point in red (clamped)
    int endx = (int)round(startX + dx * dist_px);
    int endy = (int)round(startY + dy * dist_px);
    put_pixel(cubed, endx, endy, 0xFF0000, map_w_px, map_h_px);
}



void	draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(cubed, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_cubed *cubed, t_player p, int cell)
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	i = 0;
	while (i < cell * 2) // sample around radius area
	{
		map_x = (float)(i - cell) / cell + p.x;
		j = 0;
		while (j < cell * 2)
		{
			map_y = (float)(j - cell) / cell + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					(int)(p.x * cell) + i - cell,
					(int)(p.y * cell) + j - cell,
					p.c);
			j++;
		}
		i++;
	}
}

int	make_minimap(t_cubed *cubed)
{
	int	x;
	int	y;
	int	cell;
	int	color;

	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	y = 0;
	while (cubed->data.map[y])
	{
		x = 0;
		while (cubed->data.map[y][x])
		{
			if (cubed->data.map[y][x] == '1')
				color = 0xFFFFFF;
			else if (cubed->data.map[y][x] == '0')
				color = 0x0FF000;
			else
				color = -1;
			if (color != -1)
				draw_cell(cubed, x * cell, y * cell, cell, color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int	render_next_frame(t_cubed *cubed)
{
	int	cell;

	update_player(cubed);
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	if (make_minimap(cubed) == ERROR)
		return (ERROR);
	draw_player(cubed, cubed->p, cell);
	// draw_ray(cubed, cubed->p, cell);

	cast_ray(cubed, cubed->p.angle, cell);

	// draw the ray
	draw_ray_line(cubed, cubed->p.angle, cell);

	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, cubed->mlx.img, 0, 0);
	return (SUCCESS);
}

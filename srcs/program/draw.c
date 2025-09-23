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
	draw_ray(cubed, cubed->p, cell);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, cubed->mlx.img, 0, 0);
	return (SUCCESS);
}

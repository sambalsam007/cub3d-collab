/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:55:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/24 13:15:59 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
void	draw_wall_line(t_cubed *cubed, int i, t_ray ray, t_tex tex)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	ray.wall_t = (TILE_SIZE * HEIGHT) / \
		(ray.distance * cos(ray.angle - cubed->p.angle));
	step = (double)tex.height / ray.wall_t;
	tex_pos = (-(ray.wall_t / 2) + (HEIGHT / 2)) * step;
	y = (HEIGHT / 2) - (ray.wall_t / 2) - 1;
	while (++y < (HEIGHT / 2) + (ray.wall_t / 2))
	{
		if (y >= 0 && y < HEIGHT)
		{
			ray.tex_y = (int)tex_pos % tex.height;
			tex_pos += step;
			color = *(unsigned int *)(tex.adr + \
				(ray.tex_y * tex.size_line + ray.tex_x * (tex.bpp / 8)));
			my_mlx_pixel_put(cubed, i, y, color);
		}
	}
}


void	first_last_ray(t_cubed *cubed, int i, int rays)
{
	if (i == 0)
	{
		cubed->minimap.first_x = cubed->ray.hit_x;
		cubed->minimap.first_y = cubed->ray.hit_y;
	}
	if (i == rays - 1)
	{
		cubed->minimap.last_x = cubed->ray.hit_x;
		cubed->minimap.last_y = cubed->ray.hit_y;
	}
}



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




//Main render functie waar alles uit vertrekt
//Een loop die alle rays doet
// stuurt ray
// tekent 3d representatie
//tekent minimap doen we op het einde (map + speler + eerste/laatste rays)
//mlx_put_image_to_window
int	render_next_frame(t_cubed *cubed)
{
	int		i;
	int		num_rays;
	float	angle_step;

	reset_background(cubed);
	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL
	num_rays = WIDTH;
	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cast_ray(cubed, cubed->ray.angle, TILE_SIZE); // FUNCTIE VOOR DE RAY - SAMUEL
		draw_wall_line(cubed, i, cubed->ray, cubed->texture[cubed->ray.side]); // FUNCTIE TEKENEN 3D - PARIS
		// if (i == 0 || i == num_rays - 1) // MINIMAP
		// 	first_last_ray(cubed, i, num_rays);// PARIS
		//update_minimap(cubed, i, num_rays, cubed->ray); // MINIMAP - PARIS EXTRA
	}
	draw_minimap(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, \
		cubed->mlx.img, 0, 0);
	return (SUCCESS);
}


// OLD RENDER
// int	render_next_frame(t_cubed *cubed)
// {
// 	int	cell;

// 	update_player(cubed);
// 	if (get_cell_size(cubed, &cell, &cell) == ERROR)
// 		return (ERROR);
// 	if (make_minimap(cubed) == ERROR)
// 		return (ERROR);
// 	draw_player(cubed, cubed->p, cell);
// 	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, cubed->mlx.img, 0, 0);
// 	return (SUCCESS);
// }

//process is de hoofd functie om heel de programa te laten lopen en visualiseren
//Dees is een grote loop die de heletijd wacht tot "ESC" of "x" word gedrukt boven links
//het neemt mlx_hook om singiale van keybinds te ontvangen
int	process(t_cubed *cubed)
{
	mlx_hook(cubed->mlx.win, 2, 1L<<0, key_press, cubed);
	mlx_hook(cubed->mlx.win, 3, 1L<<1, key_release, cubed);
	mlx_hook(cubed->mlx.win, 17, 0, close_window, cubed);
	mlx_loop_hook(cubed->mlx.mlx, render_next_frame, cubed);
	mlx_loop(cubed->mlx.mlx);
	return (SUCCESS);
}

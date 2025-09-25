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



// samuel edit 09.25
// calculates tex_x tex_y
void _s_draw_wall_line(t_cubed *cubed, int i, t_ray *ray, t_tex tex)
{
    // use ray->tex_x instead of ray.tex_x
    double perpDist = ray->distance * cos(ray->angle - cubed->p.angle);
    if (perpDist < 1e-6)
        perpDist = 1e-6;

    int lineHeight = (int)(HEIGHT / perpDist);

    double wallX;
    if (ray->side == NORTH || ray->side == SOUTH)
        wallX = cubed->p.x + perpDist * cos(ray->angle);
    else
        wallX = cubed->p.y + perpDist * sin(ray->angle);
    wallX -= floor(wallX);

    ray->tex_x = (int)(wallX * (double)tex.width);
    if (ray->side == SOUTH || ray->side == WEST)
        ray->tex_x = tex.width - ray->tex_x - 1;

    double step = (double)tex.height / lineHeight;
    double texPos = (-(lineHeight / 2.0) + (HEIGHT / 2.0)) * step;

    int y = (HEIGHT / 2) - (lineHeight / 2);
    if (y < 0) y = 0;
    while (y < (HEIGHT / 2 + lineHeight / 2) && y < HEIGHT)
    {
        ray->tex_y = (int)texPos & (tex.height - 1);
        texPos += step;
        // int color = *(unsigned int *)(tex.adr + (ray->tex_y * tex.size_line + ray->tex_x * (tex.bpp / 8)));
        // my_mlx_pixel_put(cubed, i, y, color);
        y++;
    }
}


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

		// samuel edit 09.25
		// reset_background(cubed);

		// samuel edit 09.25
		// maybe rewrite this
		int cell;
		if (get_cell_size(cubed, &cell, &cell) == ERROR)
			return (ERROR);
		_s_draw_minimap(cubed);
		_s_draw_player(cubed, cubed->p, cell);
		_s_draw_ray_line(cubed, cubed->p.angle, cell);

	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL

	// samuel edit 09.25
	// TODO change
	num_rays = WIDTH;
	// num_rays = 2; // temporary, for better speed

	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{

		// samuel edit 09.25
		// print a line every 100 rays
		if (i % 100 == 0) 
				_s_draw_ray_line(cubed, cubed->ray.angle, cell); 
		// calculate stuff
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cubed->ray.distance = _s_cast_ray(cubed, cubed->ray.angle, cell);
		// wall
        double wall_height = (TILE_SIZE * HEIGHT) / cubed->ray.distance; // ray.distance must be fish-eye corrected
        cubed->ray.wall_t = (HEIGHT / 2) - (wall_height / 2);
        cubed->ray.wall_b = (HEIGHT / 2) + (wall_height / 2);


		// this only prints info
		if (i == (num_rays / 2))
				_s_display_ray_struct_info(cubed, i);

		_s_draw_wall_line(cubed, i, &cubed->ray, cubed->texture[cubed->ray.side]);


		// samuel edit 09.25
		// cast_ray(cubed, cubed->ray); // FUNCTIE VOOR DE RAY - SAMUEL
		
		// samuel edit 09.25
		// draw_wall_line(cubed, i, cubed->ray, cubed->texture[cubed->ray.side]); // FUNCTIE TEKENEN 3D - PARIS


		// if (i == 0 || i == num_rays - 1) // MINIMAP
		// 	first_last_ray(cubed, i, num_rays);// PARIS
		//update_minimap(cubed, i, num_rays, cubed->ray); // MINIMAP - PARIS EXTRA
	}

	// samuel edit 09.25
	// draw_minimap(cubed);

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

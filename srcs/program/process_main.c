/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:55:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/23 21:20:23 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
void	draw_wall_line(t_cubed *cubed, int i, t_ray ray, t_tex tex)
{
	double	wall_h;
	int		x;
	int		y;
	
	x = i - 1;
	ray.distance * cos(ray.angle - cubed->p.angle);
	wall_h = (TILE_SIZE * HEIGHT) / \
		(ray.distance * cos(ray.angle - cubed->p.angle));
	while (++x <= i)
	{
		
	}
	for (int x = i; x <= i; x++)
	{
		ray.wall_t = (double)tex.height / wall_h;
		ray.wall_b = (ray.wall_t - HEIGHT / 2 + wall_h / 2) * ray.wall_t;

		for (int y = ray.wall_t; y < ray.wall_b; y++)
		{
			int tex_y = (int)ray.wall_b & (tex.height - 1);
			ray.wall_b += ray.wall_t;

			char *tex_pixel = tex.adr + (tex_y * tex.size_line
				+ tex_x * (tex.bpp / 8));

			my_mlx_pixel_put(&cubed->mlx, x, y, * (unsigned int*)tex_pixel);
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

	reset_background(cubed);
	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL
	num_rays = WIDTH;
	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cubed->ray = cast_ray(cubed, cubed->ray.angle); // FUNCTIE VOOR DE RAY - SAMUEL
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
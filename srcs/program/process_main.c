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
		// _s_draw_ray_line(cubed, cubed->p.angle, cell);

	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL

	// samuel edit 09.25
	// num_rays = WIDTH;
	num_rays = 2; // temporary, for better speed

	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{





		// samuel edit 09.25
		_s_draw_ray_line(cubed, cubed->ray.angle, cell); // draw other rays
		// calculate stuff
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cubed->ray.distance = _s_cast_ray(cubed, cubed->ray.angle, cell);
		// wall
        double wall_height = (TILE_SIZE * HEIGHT) / cubed->ray.distance; // ray.distance must be fish-eye corrected
        cubed->ray.wall_t = (HEIGHT / 2) - (wall_height / 2);
        cubed->ray.wall_b = (HEIGHT / 2) + (wall_height / 2);
		// print variables
		static int frame_count = 0;
		frame_count++;
		if (frame_count % 10 == 0) // print every 10 frames
		{
				system("clear");
				printf("Frame %d\n", frame_count);
				printf("Angle\t[%d] (%f)\n", i, cubed->ray.angle);
				printf("Distn\t[%d] (%f)\n", i, cubed->ray.distance);
				printf("hit_x\t[%d] (%d)\n", i, cubed->ray.hit_x);
				printf("hit_y\t[%d] (%d)\n", i, cubed->ray.hit_y);
				if (cubed->ray.side == NORTH) printf("side\t[%d] (NORTH)\n", i);
				else if (cubed->ray.side == SOUTH) printf("side\t[%d] (SOUTH)\n", i);
				else if (cubed->ray.side == EAST) printf("side\t[%d] (EAST)\n", i);
				else if (cubed->ray.side == WEST) printf("side\t[%d] (WEST)\n", i);
				printf("wall_t\t[%d] (%lf)\n", i, cubed->ray.wall_t);
				printf("wall_b\t[%d] (%lf)\n", i, cubed->ray.wall_b);
				printf("tex_x\t[%d] (%d)\n", i, cubed->ray.tex_x);
				printf("tex_y\t[%d] (%d)\n", i, cubed->ray.tex_y);
				printf("\n");
				// for readablility
				if (i == num_rays-1)
						printf("-------------------\n");
		}



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

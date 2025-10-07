/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:55:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/26 16:19:00 by pdaskalo         ###   ########.fr       */
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
			ray.tex_y = (int)tex_pos;
			if (ray.tex_y < 0)
				ray.tex_y = 0;
			if (ray.tex_y >= tex.height)
				ray.tex_y = tex.height - 1;
			tex_pos += step;
			if (ray.tex_x < 0)
				ray.tex_x = 0;
			if (ray.tex_x >= tex.width)
				ray.tex_x = tex.width - 1;
			color = *(unsigned int *)(tex.adr + \
				(ray.tex_y * tex.size_line + ray.tex_x * (tex.bpp / 8)));
			my_mlx_pixel_put(cubed, i, y, color);
		}
	}
}

// void	draw_wall_line(t_cubed *cubed, int i, t_ray ray, t_tex tex)
// {
// 	double	step;
// 	double	tex_pos;
// 	int		y;
// 	int		color;

// 	ray.wall_t = (TILE_SIZE * HEIGHT) / \
// 		(ray.distance * cos(ray.angle - cubed->p.angle));
// 	step = (double)tex.height / ray.wall_t;
// 	tex_pos = (-(ray.wall_t / 2) + (HEIGHT / 2)) * step;
// 	y = (HEIGHT / 2) - (ray.wall_t / 2) - 1;
// 	while (++y < (HEIGHT / 2) + (ray.wall_t / 2))
// 	{
// 		if (y >= 0 && y < HEIGHT)
// 		{
// 			ray.tex_y = (int)tex_pos % tex.height;
// 			tex_pos += step;
// 			color = *(unsigned int *)(tex.adr + \
// 				(ray.tex_y * tex.size_line + ray.tex_x * (tex.bpp / 8)));
// 			my_mlx_pixel_put(cubed, i, y, color);
// 		}
// 	}
// }

static void	init_dda(t_cubed *cubed, double dirx, double diry)
{
	cubed->dda.map_x = (int)cubed->p.x;
	cubed->dda.map_y = (int)cubed->p.y;
	cubed->dda.delta_x = (fabs(dirx) > 1e-9) ? fabs(1.0 / dirx) : 1e30;
	cubed->dda.delta_y = (fabs(diry) > 1e-9) ? fabs(1.0 / diry) : 1e30;
	if (dirx < 0)
	{
		cubed->dda.step_x = -1;
		cubed->dda.side_dist_x = (cubed->p.x - cubed->dda.map_x) * cubed->dda.delta_x;
	}
	else
	{
		cubed->dda.step_x = 1;
		cubed->dda.side_dist_x = (cubed->dda.map_x + 1.0 - cubed->p.x) * cubed->dda.delta_x;
	}
	if (diry < 0)
	{
		cubed->dda.step_y = -1;
		cubed->dda.side_dist_y = (cubed->p.y - cubed->dda.map_y) * cubed->dda.delta_y;
	}
	else
	{
		cubed->dda.step_y = 1;
		cubed->dda.side_dist_y = (cubed->dda.map_y + 1.0 - cubed->p.y) * cubed->dda.delta_y;
	}
	cubed->dda.hit = 0;
}

static void	step_dda(t_cubed *cubed)
{
	if (cubed->dda.side_dist_x < cubed->dda.side_dist_y)
	{
		cubed->dda.side_dist_x += cubed->dda.delta_x;
		cubed->dda.map_x += cubed->dda.step_x;
		cubed->dda.side = 0;
	}
	else
	{
		cubed->dda.side_dist_y += cubed->dda.delta_y;
		cubed->dda.map_y += cubed->dda.step_y;
		cubed->dda.side = 1;
	}
	if (cubed->data.map[cubed->dda.map_y][cubed->dda.map_x] == '1')
		cubed->dda.hit = 1;
}

static void	finish_dda(t_cubed *cubed, double dirx, double diry, t_ray *ray)
{
	double	dist;
	double	wall_x;
	t_tex	tex;

	if (cubed->dda.side == 0)
		dist = (cubed->dda.map_x - cubed->p.x + \
			(1 - cubed->dda.step_x) / 2.0) / dirx;
	else
		dist = (cubed->dda.map_y - cubed->p.y + \
			(1 - cubed->dda.step_y) / 2.0) / diry;
	ray->distance = fabs(dist) * TILE_SIZE;
	ray->side = (cubed->dda.side == 0) ? \
		(dirx > 0 ? EAST : WEST) : (diry > 0 ? SOUTH : NORTH);
	ray->hit_x = (int)((cubed->p.x + dirx * dist) * TILE_SIZE);
	ray->hit_y = (int)((cubed->p.y + diry * dist) * TILE_SIZE);
	/* texture X */
	tex = cubed->texture[ray->side];
	wall_x = (cubed->dda.side == 0) ? (cubed->p.y + dist * diry) \
		: (cubed->p.x + dist * dirx);
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * tex.width);
	if ((cubed->dda.side == 0 && dirx > 0) || \
		(cubed->dda.side == 1 && diry < 0))
		ray->tex_x = tex.width - ray->tex_x - 1;
}

void	cast_ray(t_cubed *cubed, t_ray *ray, t_tex *tex)
{
	double	dirx;
	double	diry;

	(void)tex;
	dirx = cos(ray->angle);
	diry = sin(ray->angle);
	init_dda(cubed, dirx, diry);
	while (!cubed->dda.hit)
		step_dda(cubed);
	finish_dda(cubed, dirx, diry, ray);
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
	// maybe rewrite this...
	int cell;
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	// samuel edit 09.25
	// this draws the direction ray
	// not necessary...
	// _s_draw_ray_line(cubed, cubed->p.angle, cell);

	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL (done)
	num_rays = WIDTH;
	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{
		reset_background(cubed);

		// samuel edit 09.25 
		// fills the ray struct
		// _s_make_ray_calculations(cubed, i, angle_step, cell);
			
		// samuel edit 09.25
		// print a ray every 100 rays
		// (so the program doesnt slow down)
		// if (i % 100 == 0) 
		// 		_s_draw_ray_line(cubed, cubed->ray.angle, cell); 

		// samuel edit 09.25
		// this prints info about the middle ray / direction ray
		// if (i == (num_rays / 2))
		// 		_s_display_ray_struct_info(cubed, i);
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cast_ray(cubed, &cubed->ray, cubed->texture); // FUNCTIE VOOR DE RAY - SAMUEL
		draw_wall_line(cubed, i, cubed->ray, cubed->texture[cubed->ray.side]); // FUNCTIE TEKENEN 3D - PARIS


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

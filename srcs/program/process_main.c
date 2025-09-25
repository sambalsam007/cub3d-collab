/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:55:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/25 21:14:59 by pdaskalo         ###   ########.fr       */
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

static void	init_ray_dir(t_ray *ray, double angle,
		double *rayDirX, double *rayDirY)
{
	ray->angle = angle;
	*rayDirX = cos(angle);
	*rayDirY = sin(angle);
}

static void	init_dda(t_player *p, double rayDirX, double rayDirY,
		int *mapX, int *mapY, int *stepX, int *stepY,
		double *sideDistX, double *sideDistY,
		double *deltaDistX, double *deltaDistY)
{
	*mapX = (int)p->x;
	*mapY = (int)p->y;
	*deltaDistX = (fabs(rayDirX) > 1e-9) ? fabs(1.0 / rayDirX) : 1e9;
	*deltaDistY = (fabs(rayDirY) > 1e-9) ? fabs(1.0 / rayDirY) : 1e9;
	if (rayDirX < 0)
		*stepX = -1, *sideDistX = (p->x - *mapX) * *deltaDistX;
	else
		*stepX = 1, *sideDistX = (*mapX + 1.0 - p->x) * *deltaDistX;
	if (rayDirY < 0)
		*stepY = -1, *sideDistY = (p->y - *mapY) * *deltaDistY;
	else
		*stepY = 1, *sideDistY = (*mapY + 1.0 - p->y) * *deltaDistY;
}

static int	dda_step(t_cubed *cubed, int *mapX, int *mapY,
		double *sideDistX, double *sideDistY,
		double deltaDistX, double deltaDistY,
		int stepX, int stepY, int *side)
{
	while (1)
	{
		if (*sideDistX < *sideDistY)
			*sideDistX += deltaDistX, *mapX += stepX, *side = 0;
		else
			*sideDistY += deltaDistY, *mapY += stepY, *side = 1;
		if (*mapY < 0 || *mapX < 0 || !cubed->data.map[*mapY]
			|| cubed->data.map[*mapY][*mapX] == '\0')
			return (0);
		if (cubed->data.map[*mapY][*mapX] == '1')
			return (1);
	}
}

static t_compas	get_side(int side, double rayDirX, double rayDirY)
{
	if (side == 0)
		return (rayDirX > 0 ? EAST : WEST);
	return (rayDirY > 0 ? SOUTH : NORTH);
}

void	cast_ray(t_cubed *cubed, t_ray *ray, t_tex *tex)
{
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		side;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpDist;
	double	wallX;

	init_ray_dir(ray, ray->angle, &rayDirX, &rayDirY);
	init_dda(&cubed->p, rayDirX, rayDirY, &mapX, &mapY,
		&stepX, &stepY, &sideDistX, &sideDistY, &deltaDistX, &deltaDistY);
	if (!dda_step(cubed, &mapX, &mapY, &sideDistX, &sideDistY,
			deltaDistX, deltaDistY, stepX, stepY, &side))
		return ;
	if (side == 0)
		perpDist = (mapX - cubed->p.x + (1 - stepX) / 2.0) / rayDirX;
	else
		perpDist = (mapY - cubed->p.y + (1 - stepY) / 2.0) / rayDirY;
	ray->distance = fabs(perpDist) * TILE_SIZE;
	ray->side = get_side(side, rayDirX, rayDirY);
	ray->hit_x = (int)((cubed->p.x + rayDirX * perpDist) * TILE_SIZE);
	ray->hit_y = (int)((cubed->p.y + rayDirY * perpDist) * TILE_SIZE);
	if (side == 0)
		wallX = cubed->p.y + perpDist * rayDirY;
	else
		wallX = cubed->p.x + perpDist * rayDirX;
	wallX -= floor(wallX);
	ray->tex_x = (int)(wallX * tex->width);
	if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
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
	reset_background(cubed);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:55:21 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/22 20:45:56 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

	update_player(cubed); // UPDATE DE FUNCTIE VOOR ROTATIE - SAMUEL
	num_rays = WIDTH;
	angle_step = cubed->p.fov / (float)num_rays;
	i = -1;
	while (++i < num_rays)
	{
		cubed->ray.angle = cubed->p.angle - (cubed->p.fov / 2.0f) + (i * angle_step);
		cubed->ray = cast_ray(cubed, cubed->ray.angle); // FUNCTIE VOOR DE RAY - SAMUEL
		draw_wall_line(cubed, i, cubed->ray); // FUNCTIE TEKENEN 3D - PARIS
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
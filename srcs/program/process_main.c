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

// process is de hoofd functie om heel de programa te laten lopen en 
// visualiseren.
// Dees is een grote loop die de heletijd wacht tot "ESC" of "x" word gedrukt 
// boven links.
// het neemt mlx_hook om singiale van keybinds te ontvangen
//
// dirX, dirY	= the direction the player faces when spawning
// planeX, ...	= these coordinates are used to calculate FOV

int	process(t_cubed *cubed)
{
	cubed->p.dirX = 1.0;
	cubed->p.dirY = 0.0;
	cubed->p.planeX = 0.0;
	cubed->p.planeY = 0.66;
	mlx_hook(cubed->mlx.win, 2, 1L << 0, key_press, cubed);
	mlx_hook(cubed->mlx.win, 3, 1L << 1, key_release, cubed);
	mlx_hook(cubed->mlx.win, 17, 0, close_window, cubed);
	mlx_loop_hook(cubed->mlx.mlx, _s2_render_next_frame, cubed);
	mlx_loop(cubed->mlx.mlx);
	return (SUCCESS);
}

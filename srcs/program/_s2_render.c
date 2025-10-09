/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:55:02 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 13:55:03 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void _s2_put_pixel(t_cubed *cubed, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) 
	    return;
    char *dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
    *(unsigned int*)dst = (unsigned int)color;
}

// not used?
static void _s2_draw_vline(t_cubed *cubed, int x, int y0, int y1, int color)
{
    if (x < 0 || x >= WIDTH) 
	    return;
    if (y0 < 0) y0 = 0;
    if (y1 >= HEIGHT) y1 = HEIGHT - 1;
    for (int y = y0; y <= y1; ++y) 
	    _s2_put_pixel(cubed, x, y, color);
}

// note:	in the loop, starting from define_texture_compass(), it's
// 		mostly functions relating to texture
static void	_s2_render_scene(t_cubed *c)
{
	int	x;

	x = 0;
	reset_background(c);
	while (x < WIDTH)
	{
		t_ray r = c->ray;
		general_calculations(c, &r, x);
		texture_calculations(c, &r, x);
		x++;
	}
	_s_draw_minimap(c);
	mlx_put_image_to_window(c->mlx.mlx, c->mlx.win, c->mlx.img, 0, 0);
}

int	_s2_render_next_frame(t_cubed *cubed)
{
	int cell;

	update_player(cubed);
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	_s2_render_scene(cubed);
	return (SUCCESS);
}

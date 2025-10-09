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

void	_s2_put_pixel(t_cubed *c, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = c->mlx.adr + (y * c->mlx.size_line + x * (c->mlx.bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

// note:	in the loop, starting from define_texture_compass(), it's
// 		mostly functions relating to texture
static void	_s2_render_scene(t_cubed *c)
{
	int		x;
	t_ray	r;

	x = 0;
	reset_background(c);
	while (x < WIDTH)
	{
		r = c->ray;
		general_calculations(c, &r, x);
		texture_calculations(c, &r, x);
		x++;
	}
	_s_draw_minimap(c);
	mlx_put_image_to_window(c->mlx.mlx, c->mlx.win, c->mlx.img, 0, 0);
}

int	_s2_render_next_frame(t_cubed *cubed)
{
	int	cell;

	update_player(cubed);
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	_s2_render_scene(cubed);
	return (SUCCESS);
}

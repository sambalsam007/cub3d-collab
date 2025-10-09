/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_textures_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:23:24 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 13:23:28 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// how much to move in the texture for each screen pixel
void	calc_step(t_ray *r)
{
	r->step = (double)r->tex_h / (double)r->line_height;
}

// starting texture y position
void	calc_tex_pos(t_ray *r)
{
	r->tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;
}

// if (side == 1) color = ...
// simple shading for horizontal walls
void	draw_vertical_column(t_cubed *c, t_ray *r, int current_ray_nbr)
{
	int		x;
	int		y;
	int		tex_y;
	int		color;
	char	*tex_pixel;

	x = current_ray_nbr;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= r->tex_h)
			tex_y = r->tex_h - 1;
		r->tex_pos += r->step;
		tex_pixel = r->tex_addr + tex_y * r->tex_line + r->texture_x * (r->tex_bpp / 8);
		color = *(int *)tex_pixel;
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		_s2_put_pixel(c, x, y, color);
		y++;
	}
}

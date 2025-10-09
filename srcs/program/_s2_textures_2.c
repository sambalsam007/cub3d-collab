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

// starting texture y position
void	calc_tex_pos(t_ray *r)
{
	r->texPos = (r->drawStart - HEIGHT / 2 + r->lineHeight / 2) * r->step;
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
	y = r->drawStart;
	while (y <= r->drawEnd)
	{
		tex_y = (int)r->texPos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= r->texH)
			tex_y = r->texH - 1;
		r->texPos += r->step;
		tex_pixel = r->texAddr + tex_y * r->texLine + r->texX * (r->texBpp / 8);
		color = *(int *)tex_pixel;
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		_s2_put_pixel(c, x, y, color);
		y++;
	}
}

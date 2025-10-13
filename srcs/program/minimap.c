/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:53:10 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/13 11:53:12 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// func: draw certain cell/tile on the img, in true size 
// 				(so at its pixel position)
// input:
// x = PIXEL x position of the top-left corner of the cell/tile
// y = PIXEL y position of the top left corner of the cell/tile
// int size = PIXEL size 1 cell/tile (H, L)
// color = color to use
//
// loop over every pixel inside one cell
//
// x, y are top left corner
// so we do x+i and y+j to fill the entire cell
// we draw a pixel at (x+i, y+j)
void	draw_cell(t_cubed *cubed, int x, int y, t_minimap *m)
{
	int	i;
	int	j;
	int	size;
	int	color;

	i = 0;
	size = m->scale;
	color = m->color;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(cubed, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	iterate_over_minimap(t_cubed *cubed, t_minimap *m)
{
	while (cubed->data.map[m->y])
	{
		m->x = 0;
		while (cubed->data.map[m->y][m->x])
		{
			if (cubed->data.map[m->y][m->x] == '1')
				m->color = 0xFFFFFF;
			else if (cubed->data.map[m->y][m->x] == '0')
				m->color = 0x00FF00;
			else
				m->color = -1;
			if (m->color != -1)
				draw_cell(cubed,
					m->offset_x + m->x * m->scale,
					m->offset_y + m->y * m->scale,
					m);
			m->x++;
		}
		m->y++;
	}
}

// m.scale = ... => shrink to 30%
// map_width ._height = ... => place minimap in top-right
// width of minimap = num_cols * scale
// m.offset_x = ... => 10px margin from right
// m.offset_y = ... => 10px margin from top
int	minimap_settings(t_cubed *cubed, t_minimap *m)
{
	if (get_cell_size(cubed, &m->cell, &m->cell) == ERROR)
		return (ERROR);
	m->scale = (int)(m->cell * 0.3);
	m->map_width = ft_strlen(cubed->data.map[0]) * m->scale;
	m->map_height = 0;
	while (cubed->data.map[m->map_height])
		m->map_height++;
	m->map_height *= m->scale;
	m->offset_x = WIDTH - m->map_width - 10;
	m->offset_y = 10;
	m->y = 0;
	return (0);
}

// if (cubed->data.map[m.y][m.x] == '1')
// 	=> wall color
// else if (cubed->data.map[m.y][m.x] == '0')
// 	=> floor color
int	draw_minimap(t_cubed *cubed)
{
	t_minimap	m;

	if (minimap_settings(cubed, &m) == ERROR)
		return (ERROR);
	iterate_over_minimap(cubed, &m);
	draw_player(cubed, cubed->p, m);
	draw_player_ray(cubed, cubed->p, m);
	return (SUCCESS);
}

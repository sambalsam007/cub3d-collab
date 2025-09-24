/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:48:32 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/22 21:02:23 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			my_mlx_pixel_put(cubed, x + i, y + j, color);
	}
}

void	draw_player(t_cubed *cubed, t_player p, int cell)// 2 RAYS TEKENEN MET BERSHINHAM ALGO - SAMUEL
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	i = -1;
	while (++i < cell * 2)
	{
		map_x = (float)(i - cell) / cell + p.x;
		j = -1;
		while (++j < cell * 2)
		{
			map_y = (float)(j - cell) / cell + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					(int)(p.x * cell) + i - cell,
					(int)(p.y * cell) + j - cell,
					p.c);
		}
	}
}

void	draw_minimap(t_cubed *cubed)
{
	int	x;
	int	y;
	int	cell;

	cell = cubed->minimap.scale;
	y = -1;
	while (cubed->data.map[++y])
	{
		x = -1;
		while (cubed->data.map[y][++x])
		{
			if (cubed->data.map[y][x] == '1')
				draw_cell(cubed, WIDTH - 15 - cubed->minimap.width \
					+ x * cell, y * cell + 15, cell, 0xFFFFFF);
			else if (cubed->data.map[y][x] == '0')
				draw_cell(cubed, WIDTH - 15 - cubed->minimap.width \
					+ x * cell, y * cell + 15, cell, 0x808080);
		}
	}
	draw_player(cubed, cubed->p, cell);
}

// samuel---
// clears screen,
// no leftover pixels from prev. render
// draw base colors for sky/ceiling and floor
// ---samue
void	reset_background(t_cubed *cubed)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(cubed, x, y, cubed->data.color_c);
			else
				my_mlx_pixel_put(cubed, x, y, cubed->data.color_f);
		}
	}
}

// int	make_minimap(t_cubed *cubed)
// {
// 	int	x;
// 	int	y;
// 	int	cell;
// 	int	color;

// 	if (get_cell_size(cubed, &cell, &cell) == ERROR)
// 		return (ERROR);
// 	y = -1;
// 	while (cubed->data.map[++y])
// 	{
// 		x = -1;
// 		while (cubed->data.map[y][++x])
// 		{
// 			if (cubed->data.map[y][x] == '1')
// 				color = 0xFFFFFF;
// 			else if (cubed->data.map[y][x] == '0')
// 				color = 0x0FF000;
// 			else
// 				color = -1;
// 			if (color != -1)
// 				draw_cell(cubed, x * cell, y * cell, cell, color);
// 		}
// 	}
// 	return (SUCCESS);
// }

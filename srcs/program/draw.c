/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:48:32 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:55:45 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_cell(t_cubed *cubed, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
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

void	draw_player(t_cubed *cubed, t_player p, int cell)
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	i = 0;
	while (i < cell * 2) // sample around radius area
	{
		map_x = (float)(i - cell) / cell + p.x;
		j = 0;
		while (j < cell * 2)
		{
			map_y = (float)(j - cell) / cell + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					(int)(p.x * cell) + i - cell,
					(int)(p.y * cell) + j - cell,
					p.c);
			j++;
		}
		i++;
	}
}

int	make_minimap(t_cubed *cubed)
{
	int	x;
	int	y;
	int	cell;
	int	color;

	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	y = 0;
	while (cubed->data.map[y])
	{
		x = 0;
		while (cubed->data.map[y][x])
		{
			if (cubed->data.map[y][x] == '1')
				color = 0xFFFFFF;
			else if (cubed->data.map[y][x] == '0')
				color = 0x0FF000;
			else
				color = -1;
			if (color != -1)
				draw_cell(cubed, x * cell, y * cell, cell, color);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int	render_next_frame(t_cubed *cubed)
{
	int	cell;

	update_player(cubed);
	if (get_cell_size(cubed, &cell, &cell) == ERROR)
		return (ERROR);
	if (make_minimap(cubed) == ERROR)
		return (ERROR);
	draw_player(cubed, cubed->p, cell);
	mlx_put_image_to_window(cubed->mlx.mlx, cubed->mlx.win, cubed->mlx.img, 0, 0);
	return (SUCCESS);
}

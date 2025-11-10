/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:21:06 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/22 20:07:01 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_surround(char **map, int y, int x, int h)
{
	int	rowlen;

	y = y - 1;
	if (y < 0)
		return (ERROR);
	rowlen = ft_strlen(map[y]);
	if (x >= rowlen || map[y][x] == ' ' || map[y][x] == '\0')
		return (ERROR);
	y = y + 1;
	if (y >= h)
		return (ERROR);
	rowlen = ft_strlen(map[y]);
	if (x >= rowlen || map[y][x] == ' ' || map[y][x] == '\0')
		return (ERROR);
	x = x - 1;
	if (x < 0)
		return (ERROR);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (ERROR);
	x = x + 1;
	rowlen = ft_strlen(map[y]);
	if (x >= rowlen || map[y][x] == ' ' || map[y][x] == '\0')
		return (ERROR);
	return (SUCCESS);
}

int	validate_map(t_cubed *cubed, int h, int w)
{
	int	y;
	int	x;

	y = -1;
	while (++y < h)
	{
		x = 0;
		while (x < w && cubed->data.map[y][x])
		{
			if (cubed->data.map[y][x] == '0' \
					|| is_player(cubed->data.map[y][x]))
			{
				if (check_surround(cubed->data.map, y, x, h) \
						== ERROR)
					return (ERROR);
			}
			x++;
		}
	}
	return (SUCCESS);
}

void	init_loops(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cubed->texture[i].adr = NULL;
		cubed->texture[i].found = 0;
		cubed->texture[i].img = NULL;
		cubed->texture[i].width = 0;
		cubed->texture[i].height = 0;
		cubed->texture[i].bpp = 0;
		cubed->texture[i].size_line = 0;
		cubed->texture[i].endian = 0;
		i++;
	}
	i = 0;
	while (i < 99999)
		cubed->keys[i++] = 0;
	cubed->data.color_c_found = 0;
	cubed->data.color_f_found = 0;
}

void	init(t_cubed *cubed)
{
	cubed->mlx.mlx = NULL;
	cubed->mlx.img = NULL;
	cubed->mlx.win = NULL;
	cubed->mlx.adr = NULL;
	cubed->data.map = NULL;
	cubed->data.color_c = -1;
	cubed->data.color_f = -1;
	cubed->data.cords_p[0] = -1;
	cubed->data.cords_p[1] = -1;
	cubed->data.compas = NORTH;
	cubed->last_time = get_time_ms();
	cubed->ray.angle = 0;
	cubed->ray.hit_x = 0;
	cubed->ray.hit_y = 0;
	cubed->ray.distance = 0;
	cubed->ray.side = 0;
	cubed->minimap.x = 0;
	cubed->minimap.y = 0;
	cubed->minimap.cell = 0;
	cubed->minimap.color = 0;
	cubed->minimap.scale = 0;
	cubed->minimap.offset_x = 0;
	cubed->minimap.offset_y = 0;
	init_loops(cubed);
}

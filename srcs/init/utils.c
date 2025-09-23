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

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	check_surround(char **map, int y, int x, int h)
{
	int	ny;
	int	nx;
	int	rowlen;

	ny = y - 1;
	nx = x;
	if (ny < 0)
		return (ERROR);
	rowlen = ft_strlen(map[ny]);
	if (nx >= rowlen || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	ny = y + 1;
	if (ny >= h)
		return (ERROR);
	rowlen = ft_strlen(map[ny]);
	if (nx >= rowlen || map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	ny = y;
	nx = x - 1;
	if (nx < 0)
		return (ERROR);
	if (map[ny][nx] == ' ' || map[ny][nx] == '\0')
		return (ERROR);
	nx = x + 1;
	rowlen = ft_strlen(map[ny]);
	if (nx >= rowlen || map[ny][nx] == ' ' || map[ny][nx] == '\0')
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
		x = -1;
		while (++x < w)
		{
			if (cubed->data.map[y][x] == '0' || is_player(cubed->data.map[y][x]))
			{
				if (check_surround(cubed->data.map, y, x, h) == ERROR)
					return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

void	init_player(t_cubed *cubed)
{
	cubed->p.x = cubed->data.cords_p[0] + 0.5f;
	cubed->p.y = cubed->data.cords_p[1] + 0.5f;
	cubed->p.r = 0.2f;
	cubed->p.c = 0xFF0000;
	cubed->p.fov = M_PI / 3;
	if (cubed->data.compas == NORTH)
		cubed->p.angle = -M_PI / 2;
	else if (cubed->data.compas == SOUTH)
		cubed->p.angle = M_PI / 2;
	else if (cubed->data.compas == EAST)
		cubed->p.angle = 0;
	else if (cubed->data.compas == WEST)
		cubed->p.angle = M_PI;
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
	while (i < 300)
		cubed->keys[i++] = 0;
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
	cubed->minimap.first_x = 0;
	cubed->minimap.first_y = 0;
	cubed->minimap.last_x = 0;
	cubed->minimap.last_y = 0;
	cubed->minimap.width = 0;
	cubed->minimap.height = 0;
	cubed->minimap.scale = TILE_SIZE / 4;
	init_loops(cubed);
}

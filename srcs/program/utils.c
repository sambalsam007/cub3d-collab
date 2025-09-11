/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:17:04 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:47:44 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_cell_size(t_cubed *cubed, int *w, int *h)
{
	int	width;
	int	height;
	int	cell_w;
	int	cell_h;

	width = get_map_width(cubed->data.map);
	height = ft_arrlen(cubed->data.map);
	if (width == 0 || height == 0)
		return (ERROR);
	cell_w = WIDTH / width;
	cell_h = HEIGHT / height;
	if (cell_w < cell_h)
		*w = cell_w;
	else
		*w = cell_h;
	*h = *w;
	return (SUCCESS);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_mlx_pixel_put(t_cubed *cubed, int x, int y, int color)
{
	char	*dst;

	dst = cubed->mlx.adr + (y * cubed->mlx.size_line + x * (cubed->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}
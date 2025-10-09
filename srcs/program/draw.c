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

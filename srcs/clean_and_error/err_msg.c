/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:43 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 18:13:27 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	err_msg(char *error)
{
	printf("%s\n", error);
}

void	free_mlx(t_cubed *cubed)
{
	if (cubed->mlx.img)
	{
		mlx_destroy_image(cubed->mlx.mlx, cubed->mlx.img);
		cubed->mlx.img = NULL;
	}
	if (cubed->mlx.win)
	{
		mlx_destroy_window(cubed->mlx.mlx, cubed->mlx.win);
		cubed->mlx.win = NULL;
	}
	if (cubed->mlx.mlx)
	{
		mlx_destroy_display(cubed->mlx.mlx);
		free(cubed->mlx.mlx);
		cubed->mlx.mlx = NULL;
	}
}

void	free_textures(t_cubed *cubed)
{
	t_tex	*tex;
	int		i;

	tex = cubed->texture;
	i = 0;
	while (i < 4)
	{
		if (tex[i].found == 1 && tex[i].img)
			mlx_destroy_image(cubed->mlx.mlx, tex[i].img);
		i++;
	}
}

void	free_all(t_cubed *cubed)
{
	if (cubed->data.map)
		ft_freearr(cubed->data.map);
	free_textures(cubed);
	free_mlx(cubed);
}

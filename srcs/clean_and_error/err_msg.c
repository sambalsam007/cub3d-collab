/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:07:43 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:42:47 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	err_msg(char *error)
{
	printf("%s\n", error);
}

void	free_cubed(t_cubed *cubed)
{
	if (cubed->mlx.img)
		mlx_destroy_image(cubed->mlx.mlx, cubed->mlx.img);
	if (cubed->mlx.win)
		mlx_destroy_window(cubed->mlx.mlx, cubed->mlx.win);
	if (cubed->mlx.mlx)
		free(cubed->mlx.mlx);
	return;
}
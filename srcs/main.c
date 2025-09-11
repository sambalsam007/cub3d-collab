/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:19:10 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 18:03:53 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	process(t_cubed *cubed)
{
	mlx_hook(cubed->mlx.win, 2, 1L<<0, key_press, cubed);
	mlx_hook(cubed->mlx.win, 3, 1L<<1, key_release, cubed);
	mlx_hook(cubed->mlx.win, 17, 0, close_window, cubed);
	mlx_loop_hook(cubed->mlx.mlx, render_next_frame, cubed);
	mlx_loop(cubed->mlx.mlx);
	return (free_all(cubed), SUCCESS);
}

static int	valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	return (ft_strncmp(filename, ".cub", 4) == 0);
}

int	main(int ac, char **av)
{
	t_cubed	cubed;
	
	if (ac != 2 || !valid_filename(av[1]))
		return (err_msg(ERR_USE), ERROR);
	else
	{
		if (init_cubed(&cubed, av[1]))
			return (ERROR);
		if (process(&cubed))
			return (ERROR);
	}
	return (SUCCESS);
}
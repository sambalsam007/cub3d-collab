/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:19:10 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/04 18:24:01 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	return (ft_strncmp(filename, ".cub", 4) == 0);
}

// input: path to a map
int	main(int ac, char **av)
{
	// (?) 
	// struct cubed, 
	// this contains 2 structs
	// 1. the data we need for everything
	// 2 the data we need for all the mlx stuff
	t_cubed	cubed;
	
	if (ac != 2 || !valid_filename(av[1]))
		return (err_msg(ERR_USE), ERROR);
	else
	{
		if (init_cubed(&cubed, av[1]))
			return (ERROR);
		// if (process(&cubed))
		// 	return (ERROR);
	}
	// printf("map: %s\n", cubed.data.map[3]);
	return (SUCCESS);
}

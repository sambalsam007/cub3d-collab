/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:19:10 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/22 19:55:30 by pdaskalo         ###   ########.fr       */
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

//Main branches of to all main functions being
//init_cubed dat alles parsed zoals de map muur vloer en plafond texturen en initializeerd
//process is de hoofd functie om heel de programa te laten lopen en visualiseren
int	main(int ac, char **av)
{
	t_cubed	cubed;
	
	if (ac != 2 || !valid_filename(av[1]))
		return (err_msg(ERR_USE), ERROR);
	else
	{
		if (init_cubed(&cubed, av[1]))
			return (ERROR);
		for (int i=0; cubed.data.map[i]; i++)
		{
			printf("%s\n", cubed.data.map[i]);
		}
		if (process(&cubed))
			return (ERROR);
	}
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:30 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:45:39 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	close_window(void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	free_cubed(cubed);
	return (0);
}

int	key_press(int key, t_cubed *cubed)
{
	if (key >= 0 && key < 300)
		cubed->keys[key] = 1;
	if (key == 53) // ESC
		close_window(cubed);
	return (0);
}

int	key_release(int key, t_cubed *cubed)
{
	if (key >= 0 && key < 300)
		cubed->keys[key] = 0;
	return (0);
}
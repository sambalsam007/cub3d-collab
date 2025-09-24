/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:30 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 18:28:34 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	close_window(void *param)
{
	t_cubed	*cubed;

	cubed = (t_cubed *)param;
	free_all(cubed);
	exit (0);
}

int	key_press(int key, t_cubed *cubed)
{
		printf("keycode; %d\n", key);
	if (key >= 0 && key < 300)
		cubed->keys[key] = 1;
	if (key == KEY_ESC)
		close_window(cubed);
	return (0);
}

int	key_release(int key, t_cubed *cubed)
{
	if (key >= 0 && key < 300)
		cubed->keys[key] = 0;
	return (0);
}

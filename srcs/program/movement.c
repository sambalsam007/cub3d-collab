/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:31:00 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 19:31:01 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	player_forward_backward(t_cubed *cubed)
{
	double	move_step;
	double	nx;
	double	ny;

	move_step = 0.0;
	if (cubed->keys[KEY_W])
		move_step += MOVE_SPEED;
	if (cubed->keys[KEY_S])
		move_step -= MOVE_SPEED;
	if (move_step != 0.0)
	{
		nx = cubed->p.x + cubed->p.dir_x * move_step;
		ny = cubed->p.y + cubed->p.dir_y * move_step;
		if (can_move(cubed, nx, ny))
		{
			cubed->p.x = nx;
			cubed->p.y = ny;
		}
	}
}

void	player_strafe_left_right(t_cubed *cubed)
{
	double	nx;
	double	ny;

	if (cubed->keys[KEY_A])
	{
		nx = cubed->p.x - cubed->p.plane_x * (MOVE_SPEED);
		ny = cubed->p.y - cubed->p.plane_y * (MOVE_SPEED);
		if (can_move(cubed, nx, ny))
		{
			cubed->p.x = nx;
			cubed->p.y = ny;
		}
	}
	if (cubed->keys[KEY_D])
	{
		nx = cubed->p.x + cubed->p.plane_x * (MOVE_SPEED);
		ny = cubed->p.y + cubed->p.plane_y * (MOVE_SPEED);
		if (can_move(cubed, nx, ny))
		{
			cubed->p.x = nx;
			cubed->p.y = ny;
		}
	}
}

void	player_rotate_left(t_cubed *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->p.dir_x;
	c->p.dir_x = c->p.dir_x * cos(-ROT_SPEED) \
		- c->p.dir_y * sin(-ROT_SPEED);
	c->p.dir_y = old_dir_x * sin(-ROT_SPEED) \
		+ c->p.dir_y * cos(-ROT_SPEED);
	old_plane_x = c->p.plane_x;
	c->p.plane_x = c->p.plane_x * cos(-ROT_SPEED) \
		- c->p.plane_y * sin(-ROT_SPEED);
	c->p.plane_y = old_plane_x * sin(-ROT_SPEED) \
		+ c->p.plane_y * cos(-ROT_SPEED);
}

void	player_rotate_right(t_cubed *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->p.dir_x;
	c->p.dir_x = c->p.dir_x * cos(ROT_SPEED) \
		- c->p.dir_y * sin(ROT_SPEED);
	c->p.dir_y = old_dir_x * sin(ROT_SPEED) \
		+ c->p.dir_y * cos(ROT_SPEED);
	old_plane_x = c->p.plane_x;
	c->p.plane_x = c->p.plane_x * cos(ROT_SPEED) \
		- c->p.plane_y * sin(ROT_SPEED);
	c->p.plane_y = old_plane_x * sin(ROT_SPEED) \
		+ c->p.plane_y * cos(ROT_SPEED);
}

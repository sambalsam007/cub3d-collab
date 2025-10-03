/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:45:43 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/11 15:51:14 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	can_move(t_cubed *cubed, float nx, float ny)
{
	float	r;
	int		tx;
	int		ty;

	r = cubed->p.r;
	tx = (int)(nx - r);
	ty = (int)(ny - r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx + r);
	ty = (int)(ny - r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx - r);
	ty = (int)(ny + r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	tx = (int)(nx + r);
	ty = (int)(ny + r);
	if (cubed->data.map[ty][tx] != '0')
		return (0);
	return (1);
}

int	is_in(float x, float y, t_player p)
{
	float	dist_sqrt;
	float	dist;

	dist_sqrt = sqrtf((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	dist = dist_sqrt - p.r;
	if (dist <= 0.0f)
		return (1);
	return (0);
}

void	update_player(t_cubed *cubed)
{
    // forward backward
    double moveStep = 0.0;
    if (cubed->keys[KEY_W]) moveStep += MOVE_SPEED;
    if (cubed->keys[KEY_S]) moveStep -= MOVE_SPEED;

    if (moveStep != 0.0) {
        double nx = cubed->p.x + cubed->p.dirX * moveStep;
        double ny = cubed->p.y + cubed->p.dirY * moveStep;
        if (can_move(cubed, nx, ny))
	{
		cubed->p.x = nx;
		cubed->p.y = ny;
	}
    }

    // strafe left, right
    // instead of move
    if (cubed->keys[KEY_A]) {
        double nx = cubed->p.x - cubed->p.planeX * (MOVE_SPEED);
        double ny = cubed->p.y - cubed->p.planeY * (MOVE_SPEED);
        if (can_move(cubed, nx, ny))
	{
		cubed->p.x = nx;
		cubed->p.y = ny;
	}
    }
    if (cubed->keys[KEY_D]) {
        double nx = cubed->p.x + cubed->p.planeX * (MOVE_SPEED);
        double ny = cubed->p.y + cubed->p.planeY * (MOVE_SPEED);
        if (can_move(cubed, nx, ny))
	{
		cubed->p.x = nx;
		cubed->p.y = ny;
	}
    }

    // rotate
    if (cubed->keys[KEY_J]) {
        double oldDirX = cubed->p.dirX;
        cubed->p.dirX = cubed->p.dirX * cos(-ROT_SPEED) - cubed->p.dirY * sin(-ROT_SPEED);
        cubed->p.dirY = oldDirX * sin(-ROT_SPEED) + cubed->p.dirY * cos(-ROT_SPEED);
        double oldPlaneX = cubed->p.planeX;
        cubed->p.planeX = cubed->p.planeX * cos(-ROT_SPEED) - cubed->p.planeY * sin(-ROT_SPEED);
        cubed->p.planeY = oldPlaneX * sin(-ROT_SPEED) + cubed->p.planeY * cos(-ROT_SPEED);
    }
    if (cubed->keys[KEY_K]) {
        double oldDirX = cubed->p.dirX;
        cubed->p.dirX = cubed->p.dirX * cos(ROT_SPEED) - cubed->p.dirY * sin(ROT_SPEED);
        cubed->p.dirY = oldDirX * sin(ROT_SPEED) + cubed->p.dirY * cos(ROT_SPEED);
        double oldPlaneX = cubed->p.planeX;
        cubed->p.planeX = cubed->p.planeX * cos(ROT_SPEED) - cubed->p.planeY * sin(ROT_SPEED);
        cubed->p.planeY = oldPlaneX * sin(ROT_SPEED) + cubed->p.planeY * cos(ROT_SPEED);
    }
}

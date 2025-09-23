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

// samuel added
# define ROTATION_SPEED 0.005

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
	long	now;
	float	dt;
	float	speed;
	float	nx;
	float	ny;

	now = get_time_ms();
	dt = (now - cubed->last_time) / 1000.0f; // seconds
	if (dt < 0.001f)
		dt = 0.001f;
	cubed->last_time = now;
	speed = 3.0f * dt; // 3 tiles per second
	nx = cubed->p.x;
	ny = cubed->p.y;


	if (cubed->keys[119]) // W macos 13
		ny -= speed;
	if (cubed->keys[115]) // S 1
		ny += speed;
	if (cubed->keys[97]) // A 0
		nx -= speed;
	if (cubed->keys[100]) // D 2
		nx += speed;

    // Rotation
    if (cubed->keys[106]) cubed->p.angle -= ROTATION_SPEED; // rotate left
    if (cubed->keys[107]) cubed->p.angle += ROTATION_SPEED; // rotate right

    // angel fout?
    // changed from int to double (going to fast...) but working!
    // now it works...

	if (can_move(cubed, nx, ny))
	{
		cubed->p.x = nx;
		cubed->p.y = ny;
	}
	// for rotate
	// j 106
	// k 107
}

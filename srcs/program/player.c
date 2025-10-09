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

void	draw_player(t_cubed *cubed, t_player p, int scale, int offset_x, int offset_y)
{
	int		i;
	int		j;
	float	map_x;
	float	map_y;

	// make player dot ~ 2x scale (so it's visible)
	int radius = scale * 2;

	i = 0;
	while (i < radius * 2)
	{
		map_x = (float)(i - radius) / radius + p.x;
		j = 0;
		while (j < radius * 2)
		{
			map_y = (float)(j - radius) / radius + p.y;
			if (is_in(map_x, map_y, p))
				my_mlx_pixel_put(cubed,
					offset_x + (int)(p.x * scale) + i - radius,
					offset_y + (int)(p.y * scale) + j - radius,
					p.c);
			j++;
		}
		i++;
	}
}

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

void	player_forward_backward(t_cubed *cubed)
{
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
}

void	player_strafe_left_right(t_cubed *cubed)
{
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
}

void	player_rotate_left(t_cubed *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->p.dirX;
	c->p.dirX = c->p.dirX * cos(-ROT_SPEED) \
		- c->p.dirY * sin(-ROT_SPEED);
	c->p.dirY = old_dir_x * sin(-ROT_SPEED) \
		+ c->p.dirY * cos(-ROT_SPEED);
	old_plane_x = c->p.planeX;
	c->p.planeX = c->p.planeX * cos(-ROT_SPEED) \
		- c->p.planeY * sin(-ROT_SPEED);
	c->p.planeY = old_plane_x * sin(-ROT_SPEED) \
		+ c->p.planeY * cos(-ROT_SPEED);
}

void	player_rotate_right(t_cubed *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->p.dirX;
	c->p.dirX = c->p.dirX * cos(ROT_SPEED) \
		- c->p.dirY * sin(ROT_SPEED);
	c->p.dirY = old_dir_x * sin(ROT_SPEED) \
		+ c->p.dirY * cos(ROT_SPEED);
	old_plane_x = c->p.planeX;
	c->p.planeX = c->p.planeX * cos(ROT_SPEED) \
		- c->p.planeY * sin(ROT_SPEED);
	c->p.planeY = old_plane_x * sin(ROT_SPEED) \
		+ c->p.planeY * cos(ROT_SPEED);
}

void	player_rotate(t_cubed *c)
{
	if (c->keys[KEY_J])
		player_rotate_left(c);
	if (c->keys[KEY_K])
		player_rotate_right(c);
}

void	update_player(t_cubed *cubed)
{
	player_forward_backward(cubed);
	player_strafe_left_right(cubed);
	player_rotate(cubed);
}

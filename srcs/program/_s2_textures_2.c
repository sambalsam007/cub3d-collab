/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s2_textures_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samd-hoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:23:24 by samd-hoo          #+#    #+#             */
/*   Updated: 2025/10/09 13:23:28 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// starting texture y position
void	calc_tex_pos(t_ray *r)
{
	r->texPos = (r->drawStart - HEIGHT / 2 + r->lineHeight / 2) * r->step;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:51:28 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:33:19 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;

	y = (unsigned char *)dest;
	x = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		x += n;
		y += n;
		while (n--)
			*(--y) = *(--x);
	}
	else
	{
		while (n--)
			*y++ = *x++;
	}
	return (dest);
}

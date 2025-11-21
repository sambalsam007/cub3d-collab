/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:01:34 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:33:40 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = ft_strlen((char *)dest);
	if (y >= size)
		return (ft_strlen((char *)src) + size);
	while (src[i] && (y + i) < (size - 1))
	{
		dest[y + i] = src[i];
		i++;
	}
	dest[y + i] = '\0';
	return (y + ft_strlen((char *)src));
}

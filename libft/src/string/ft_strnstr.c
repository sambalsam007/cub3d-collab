/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:10 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:33:52 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (*lil == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		x = 0;
		while (big[i + x] && (i + x < len) && lil[x]
			&& big[i + x] == lil[x])
		{
			if (lil[x + 1] == '\0')
				return ((char *)&big[i]);
			x++;
		}
		i++;
	}
	return (0);
}

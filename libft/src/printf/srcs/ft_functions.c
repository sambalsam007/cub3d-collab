/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:38:22 by pdaskalo          #+#    #+#             */
/*   Updated: 2024/10/24 15:21:29 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*pt;

	i = 0;
	pt = (unsigned char *)str;
	while (i < n)
	{
		pt[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	size_t	temp;
	void	*str;

	if (nmeb != 0 && size != 0)
	{
		temp = size * nmeb;
		if (size != temp / nmeb)
			return (NULL);
	}
	str = malloc(nmeb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, nmeb * size);
	return (str);
}

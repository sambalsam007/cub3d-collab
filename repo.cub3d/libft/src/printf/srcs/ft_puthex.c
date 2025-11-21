/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:33:30 by pdaskalo          #+#    #+#             */
/*   Updated: 2024/10/24 17:43:38 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static size_t	ft_baselen(const char *base)
{
	size_t	i;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
		i++;
	return (i);
}

static int	ft_numlen(unsigned long long x, size_t blen)
{
	int	i;

	i = 1;
	while (x >= blen)
	{
		x /= blen;
		i++;
	}
	return (i);
}

char	*ft_givebase(unsigned long long x, char *base)
{
	int		blen;
	int		len;
	char	*temp;

	blen = ft_baselen(base);
	len = ft_numlen(x, blen);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (len)
	{
		temp[--len] = base[x % blen];
		x /= blen;
	}
	return (temp);
}

int	ft_putbase(unsigned long x, char *base)
{
	int		i;
	char	*str;

	str = ft_givebase(x, base);
	if (!str)
		return (0);
	i = ft_putstr_i(str);
	return (free(str), i);
}

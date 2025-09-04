/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:41:18 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:27:11 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	c_check(char s, char c)
{
	return (c != s);
}

int	c_len(char const *str, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		while (str[i] && !c_check(str[i], c))
			i++;
		if (str[i] && c_check(str[i], c))
		{
			x++;
			while (str[i] && c_check(str[i], c))
				i++;
		}
	}
	return (x);
}

char	*c_dup(char const *str, char c)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] && c_check(str[i], c))
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && c_check(str[i], c))
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	int		x;
	char	**arr;

	arr = malloc(sizeof(char *) * (c_len(s, c) + 1));
	if (!arr)
		return (NULL);
	x = 0;
	while (*s)
	{
		while (*s && !c_check(*s, c))
			s++;
		if (*s)
		{
			arr[x] = c_dup(s, c);
			if (!arr[x])
				return (NULL);
			x++;
		}
		while (*s && c_check(*s, c))
			s++;
	}
	arr[x] = 0;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:50:47 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/09/03 13:48:29 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		x;

	x = ft_strlen((char *)s1);
	i = -1;
	join = malloc(sizeof(char) * (x + ft_strlen((char *)s2) + 1));
	if (!join)
		return (NULL);
	while (s1[++i])
		join[i] = (char)s1[i];
	i = -1;
	while (s2[++i])
		join[x + i] = (char)s2[i];
	join[i + x] = '\0';
	return (join);
}

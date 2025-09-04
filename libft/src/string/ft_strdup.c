/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:32:51 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:33:33 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = -1;
	dup = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!dup)
		return (0);
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

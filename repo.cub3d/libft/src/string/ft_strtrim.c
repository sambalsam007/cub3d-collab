/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:01 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:34:05 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	is_trimmed(char c, char *set)
{
	size_t	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char trim_char)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && s1[start] == trim_char)
		start++;
	end = ft_strlen(s1);
	while (end > start && s1[end - 1] == trim_char)
		end--;
	trim = malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (0);
	ft_strlcpy(trim, &s1[start], end - start + 1);
	return (trim);
}
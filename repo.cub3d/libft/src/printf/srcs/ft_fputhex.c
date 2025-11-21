/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:33:30 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/04/03 19:11:05 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_fputbase(unsigned long x, char *base)
{
	int		i;
	char	*str;

	str = ft_givebase(x, base);
	if (!str)
		return (0);
	i = ft_fputstr_i(str);
	return (free(str), i);
}

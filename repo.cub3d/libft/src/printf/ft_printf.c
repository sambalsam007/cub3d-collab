/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:09:01 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/04/03 19:02:10 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_type(char s, va_list va)
{
	if (s == 'c')
		return ((ft_putchar_i(va_arg(va, int))));
	else if (s == 's')
		return (ft_putstr_i(va_arg(va, char *)));
	else if (s == 'p')
		return (ft_putad_i(va_arg(va, void *)));
	else if (s == 'd' || s == 'i')
		return (ft_putnbr_i(va_arg(va, int)));
	else if (s == 'u')
		return (ft_putunbr_i(va_arg(va, unsigned int)));
	else if (s == 'X')
		return (ft_putbase(va_arg(va, unsigned int), HEXUPP));
	else if (s == 'x')
		return (ft_putbase(va_arg(va, unsigned int), HEXLOW));
	else
		return (ft_putchar_i(s));
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	va;

	if (!s)
		return (0);
	va_start(va, s);
	i = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			s++;
			i += f_type(*s, va);
		}
		else
			i += ft_putchar_i(*s);
		s++;
	}
	va_end(va);
	return (i);
}

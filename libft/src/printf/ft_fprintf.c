/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:09:01 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/04/03 19:11:01 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_type(char s, va_list va)
{
	if (s == 'c')
		return ((ft_fputchar_i(va_arg(va, int))));
	else if (s == 's')
		return (ft_fputstr_i(va_arg(va, char *)));
	else if (s == 'p')
		return (ft_fputad_i(va_arg(va, void *)));
	else if (s == 'd' || s == 'i')
		return (ft_fputnbr_i(va_arg(va, int)));
	else if (s == 'u')
		return (ft_fputunbr_i(va_arg(va, unsigned int)));
	else if (s == 'X')
		return (ft_fputbase(va_arg(va, unsigned int), HEXUPP));
	else if (s == 'x')
		return (ft_fputbase(va_arg(va, unsigned int), HEXLOW));
	else
		return (ft_fputchar_i(s));
}

int	ft_fprintf(const char *s, ...)
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
			i += ft_fputchar_i(*s);
		s++;
	}
	va_end(va);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:26:33 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/04/03 19:03:58 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_fputchar_i(char c)
{
	return (write(2, &c, 1));
}

int	ft_fputstr_i(char *str)
{
	int	i;

	if (!str)
		return (write(2, "(null)", 6));
	i = 0;
	while (str[i])
		i += ft_fputchar_i(str[i]);
	return (i);
}

int	ft_fputnbr_i(int num)
{
	long	nb;
	int		i;

	i = 0;
	nb = num;
	if (nb < 0)
	{
		i += ft_fputchar_i(45);
		nb = -nb;
	}
	if (nb > 9)
		i += ft_fputnbr_i(nb / 10);
	i += ft_fputchar_i(nb % 10 + 48);
	return (i);
}

int	ft_fputunbr_i(unsigned int num)
{
	unsigned long	nb;
	int				i;

	nb = num;
	i = ft_fputbase(nb, "0123456789");
	return (i);
}

int	ft_fputad_i(void *pt)
{
	unsigned long	x;
	int				i;

	if (!pt)
		return (i = ft_fputstr_i("(nil)"));
	i = ft_fputstr_i("0x");
	x = (unsigned long)pt;
	i += ft_fputbase(x, HEXLOW);
	return (i);
}

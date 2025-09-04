/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:26:33 by pdaskalo          #+#    #+#             */
/*   Updated: 2024/10/24 17:54:13 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar_i(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_i(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
		i += ft_putchar_i(str[i]);
	return (i);
}

int	ft_putnbr_i(int num)
{
	long	nb;
	int		i;

	i = 0;
	nb = num;
	if (nb < 0)
	{
		i += ft_putchar_i(45);
		nb = -nb;
	}
	if (nb > 9)
		i += ft_putnbr_i(nb / 10);
	i += ft_putchar_i(nb % 10 + 48);
	return (i);
}

int	ft_putunbr_i(unsigned int num)
{
	unsigned long	nb;
	int				i;

	nb = num;
	i = ft_putbase(nb, "0123456789");
	return (i);
}

int	ft_putad_i(void *pt)
{
	unsigned long	x;
	int				i;

	if (!pt)
		return (i = ft_putstr_i("(nil)"));
	i = ft_putstr_i("0x");
	x = (unsigned long)pt;
	i += ft_putbase(x, HEXLOW);
	return (i);
}

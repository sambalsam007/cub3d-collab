/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:35:00 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/04/03 19:28:59 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define HEXUPP "0123456789ABCDEF"
# define HEXLOW "0123456789abcdef"

int		ft_printf(const char *s, ...);

void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t nmeb, size_t size);

char	*ft_givebase(unsigned long long x, char *base);
int		ft_putbase(unsigned long x, char *base);

int		ft_putchar_i(char c);
int		ft_putstr_i(char *str);
int		ft_putnbr_i(int num);
int		ft_putunbr_i(unsigned int num);
int		ft_putad_i(void *pt);

int		ft_fprintf(const char *s, ...);
int		ft_fputchar_i(char c);
int		ft_fputstr_i(char *str);
int		ft_fputnbr_i(int num);
int		ft_fputunbr_i(unsigned int num);
int		ft_fputad_i(void *pt);
int		ft_fputbase(unsigned long x, char *base);

#endif

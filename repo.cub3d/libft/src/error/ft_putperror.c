/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putperror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdaskalo <pdaskalo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:08:24 by pdaskalo          #+#    #+#             */
/*   Updated: 2025/06/05 10:34:20 by pdaskalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putperror(char *msg, int exit_code)
{
	if (msg)
		perror(msg);
	if (exit_code != 0)
		exit(exit_code);
	else
		exit(1);
}

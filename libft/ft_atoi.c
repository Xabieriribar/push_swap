/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:09:22 by xiribar           #+#    #+#             */
/*   Updated: 2025/12/09 20:37:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	long	integer;
	long	sign;
	long	counter;

	counter = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		counter++;
		nptr++;
	}
	if (counter >= 2)
		return (0);
	integer = 0;
	while (ft_isdigit(*nptr))
	{
		integer = (integer * 10) + (*nptr - '0');
		nptr++;
	}
	return (integer * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:09:22 by xiribar           #+#    #+#             */
/*   Updated: 2025/09/30 15:13:41 by xiribar          ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_min(const char *nptr)
{
	int	counter;
	int	sign;

	counter = 0;
	sign = 1;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		counter++;
		nptr++;
	}
	if (counter >= 2)
		return (0);
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	long	integer;
	long	counter;
	long	sign;

	counter = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = ft_find_min(nptr);
	if (sign == 0)
		return (0);
	integer = 0;
	while (ft_isdigit(*nptr))
	{
		integer = (integer * 10) + (*nptr - '0');
		nptr++;
	}
	if (integer < INT_MIN || integer > INT_MAX)
		return (0);
	return (integer * sign);
}

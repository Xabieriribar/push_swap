/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 08:46:42 by xiribar           #+#    #+#             */
/*   Updated: 2025/11/22 08:46:42 by xiribar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_split_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

int	count_the_words(char **argv)
{
	int	counter;

	counter = 0;
	while (argv[counter])
		counter++;
	return (counter);
}

bool	ft_is_duplicate(int **numbers, t_data *data)
{
	int		index;
	int		jndex;

	index = 0;
	while (index < data->argc)
	{
		jndex = index + 1;
		while (jndex < data->argc)
		{
			if ((*numbers)[index] == (*numbers)[jndex])
				return (false);
			jndex++;
		}
		index++;
	}
	return (true);
}

static bool	is_valid_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_atol_safe(char *str, int *val)
{
	long	temp;

	if (!is_valid_syntax(str))
		return (false);
	temp = ft_atoi(str);
	if (temp < INT_MIN || temp > INT_MAX)
		return (false);
	*val = temp;
	return (true);
}

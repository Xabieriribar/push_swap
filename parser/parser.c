/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 08:46:42 by xiribar           #+#    #+#             */
/*   Updated: 2025/12/09 20:42:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
** Helper function to count arguments when they are passed as a single string
** (e.g., "./push_swap '1 2 3'").
*/
int	count_the_words(char **argv)
{
	int	counter;

	counter = 0;
	while (argv[counter])
		counter++;
	return (counter);
}

/*
** Validates that all input strings are valid integers. Allocates memory for
** the integer array and converts strings using ft_atoi.
*/
bool	ft_is_number(t_data *data, int **numbers)
{
	int		index;
	long	temp_value;
	int		j;

	index = 1;
	j = 0;
	if (data->mode)
	{
		index = 0;
		data->argc = (count_the_words(data->argv) + 1);
	}
	*numbers = malloc(sizeof(int) * (data->argc - 1));
	if (!*numbers)
		return (false);
	while (data->argv[index])
	{
		temp_value = ft_atoi(data->argv[index]);
		if (temp_value <= INT_MIN || temp_value >= INT_MAX)
			return (false);
		(*numbers)[j] = temp_value;
		j++;
		index++;
	}
	return (true);
}

/*
** Checks the integer array for duplicate numbers. 
** Push_swap requires unique values.
*/
bool	ft_is_duplicate(int **numbers, t_data *data)
{
	int		index;
	int		jndex;

	index = 0;
	while (index < data->argc - 1)
	{
		jndex = index + 1;
		while (jndex < data->argc - 1)
		{
			if ((*numbers)[index] == (*numbers)[jndex])
				return (false);
			jndex++;
		}
		index++;
	}
	return (true);
}

/*
** Main parsing controller. Handles splitting arguments if necessary, converts
** strings to numbers, and runs validation checks (duplicates, non-numbers).
*/
bool	ft_parse_input(t_data *data, int **numbers)
{
	if (data->argc == 2 && ft_strchr(data->argv[1], ' '))
	{
		data->argv = ft_split(data->argv[1], ' ');
		data->mode = 1;
	}
	if (data->argc == 1 || !ft_is_number(data, numbers)
		|| !ft_is_duplicate(numbers, data))
		return (free(data), false);
	return (true);
}

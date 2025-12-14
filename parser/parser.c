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
** Validates that all input strings are valid integers. Allocates memory for
** the integer array and converts strings using ft_atoi.
*/
static bool	ft_is_number(t_data *data, int **numbers)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (data->mode)
	{
		i = 0;
		data->argc = (count_the_words(data->argv) + 1);
	}
	*numbers = malloc(sizeof(int) * (data->argc - 1));
	if (!*numbers)
		return (false);
	while (data->argv[i])
	{
		if (!ft_atol_safe(data->argv[i], &(*numbers)[j]))
			return (free(*numbers), false);
		j++;
		i++;
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
	{
		if (data->mode == 1)
			free_split_argv(data->argv);
		return (free(data), false);
	}
	return (true);
}

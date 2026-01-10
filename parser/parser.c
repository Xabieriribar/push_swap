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

	i = 0;
	j = 0;
	*numbers = malloc(sizeof(int) * (data->argc - 1));
	if (!*numbers)
		return (false);
	while (data->argv[i])
	{
		printf("este es el problema? %c\n", data->argv[i][0]);
		if (!ft_atol_safe(data->argv[i], &(*numbers)[j]))
			return (free(*numbers), false);
		printf("value of i %d", i);
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
	int	i;
	
	i = 2;
	if (!data->argv[1][0] || data->argv[1][0] - 0 == 32)
		return (free(data), false);

	while (i < data->argc)
	{
		if (i == 2)
			data->argv[1] = ft_strjoin(data->argv[1], " ");
		data->argv[1] = ft_strjoin(data->argv[1], data->argv[i]);
		i++;
	}
	i = 0;
	printf("%s", data->argv[1]);
	if (data->argc == 1 || !ft_is_number(data, numbers)
		|| !ft_is_duplicate(numbers, data))
	{
		if (data->mode == 1)
			free_split_argv(data->argv);
		return (free(data), false);
	}
	return (true);
}

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
	*numbers = malloc(sizeof(int) * (data->argc));
	if (!*numbers)
		return (false);
	while (data->argv[i])
	{
		if (!ft_atol_safe(data->argv[i], &(*numbers)[j]))
			return (false);
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
	int		i;
	char	*temp;
	char	*joined;

	i = 1;
	joined = ft_strdup("");
	while (i < data->argc)
	{
		temp = ft_strjoin(joined, data->argv[i]);
		free(joined);
		joined = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	data->argv = ft_split(joined, ' ');
	free(joined);
	if (!data->argv)
		return (false);
	data->mode = 1;
	data->argc = count_the_words(data->argv);
	if (data->argc == 0 || !ft_is_number(data, numbers)
		|| !ft_is_duplicate(numbers, data))
		return (false);
	return (true);
}

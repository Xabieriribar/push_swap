/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/22 08:46:42 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/22 08:46:43 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int		count_the_words(char **argv)
{
	int counter;

	counter = 0;
	while (argv[counter])
		counter++;
	return (counter);
}
bool	ft_is_number(t_data *data, int **numbers)
{
	int	index;
	int	j;

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
		(*numbers)[j] = ft_atoi(data->argv[index]);
		if (!(*numbers)[j])
			return (false);
		j++;
		index++;
	}
	return (true);
}

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

bool	ft_parse_input(t_data *data, int **numbers)
{
	if (data->argc == 2 && ft_strchr(data->argv[1], ' '))
	{
		data->argv = ft_split(data->argv[1], ' ');
		data->mode = 1;
	}
	if (data->argc == 1 || !ft_is_number(data, numbers)
		|| !ft_is_duplicate(numbers, data))
		return (false);
	return (true);
}

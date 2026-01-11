/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   push_swap.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: xiribar <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/22 08:44:34 by xiribar        #+#    #+#                */
/*   Updated: 2025/11/22 08:44:40 by xiribar        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Checks if the list is already sorted in ascending order.
*/
bool	ft_is_sorted(t_stack *list)
{
	if (!list)
		return (true);
	while (list->next != NULL)
	{
		if (list->number > list->next->number)
			return (false);
		list = list->next;
	}
	return (true);
}

/*
** Initializes the main data structure with arguments.
*/
int	initialise_data(int argc, char **argv, t_data *data)
{
	data->argc = argc;
	data->argv = argv;
	data->mode = 0;
	return (1);
}

/*
** Clean-up function to free the main structure, the integer array, and
** both linked lists before the program exits.
*/
void	free_data(t_data *data, int *nbr, t_stack **list_a, t_stack **list_b)
{
	if (data && data->mode == 1)
		free_split_argv(data->argv);
	free(data);
	free(nbr);
	stack_clear(list_a);
	stack_clear(list_b);
}

/*
** Helper to select the appropriate sorting strategy based on stack size.
*/
static void	handle_sorting(t_stack **list_a, t_stack **list_b)
{
	int	size;

	size = stack_size(*list_a);
	if (size == 2)
		sort_two(list_a);
	else if (size == 3)
		sort_three(list_a);
	else if (size >= 4)
		sort_turks(list_a, list_b);
}

/*
** Entry point. Handles argument parsing, list creation, and selects the
** appropriate sorting strategy (2, 3, or Turk Algorithm) based on input size.
*/
int	main(int argc, char **argv)
{
	int			*numbers;
	t_stack		*list_a;
	t_stack		*list_b;
	t_data		*data;

	if (argc < 2)
		return (0);
	list_a = NULL;
	list_b = NULL;
	numbers = NULL;
	data = malloc(sizeof(struct s_data));
	if (!data)
		return (EXIT_FAILURE);
	initialise_data(argc, argv, data);
	if (!ft_parse_input(data, &numbers))
	{
		free_data(data, numbers, &list_a, &list_b);
		return (write(2, "Error\n", 6), 1);
	}
	stack_fill(&list_a, numbers, data->argc);
	if (list_a && !ft_is_sorted(list_a))
		handle_sorting(&list_a, &list_b);
	return (free_data(data, numbers, &list_a, &list_b), 0);
}

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
** Refreshes the `index` attribute for every node in both lists. This must be
** called after every push or rotation operation to keep positions accurate.
*/
void	update_indexes(t_list **list_a, t_list **list_b)
{
	t_list	*temp;
	int		index;

	if (list_a != NULL)
	{
		index = 0;
		temp = *list_a;
		while (temp != NULL)
		{
			temp->index = index;
			index++;
			temp = temp->next;
		}
	}
	if (list_b == NULL)
		return ;
	temp = *list_b;
	index = 0;
	while (temp != NULL)
	{
		temp->index = index;
		index++;
		temp = temp->next;
	}
}

/*
** Checks if the list is already sorted in ascending order.
*/
bool	ft_is_sorted(t_list *list)
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
	if (argc < 2)
		return (free(data), 0);
	data->argc = argc;
	data->argv = argv;
	data->mode = 0;
	return (1);
}

/*
** Clean-up function to free the main structure, the integer array, and
** both linked lists before the program exits.
*/
void	free_data(t_data *data, int *nbr, t_list **list_a, t_list **list_b)
{
	if (data && data->mode == 1)
		free_split_argv(data->argv);
	free(data);
	free(nbr);
	ft_lstclear(list_a);
	ft_lstclear(list_b);
}

/*
** Entry point. Handles argument parsing, list creation, and selects the
** appropriate sorting strategy (2, 3, or Turk Algorithm) based on input size.
*/
int	main(int argc, char **argv)
{
	int			*numbers;
	t_list		*list_a;
	t_list		*list_b;
	t_data		*data;

	list_a = NULL;
	list_b = NULL;
	numbers = NULL;
	data = malloc(sizeof(struct s_data));
	if (!data || !initialise_data(argc, argv, data))
		return (EXIT_FAILURE);
	if (!ft_parse_input(data, &numbers))
		return (write(STDERR_FILENO, "Error\n", 6), 1);
	// #ifdef 0;
	ft_fill_list(&list_a, numbers, data->argc);
	if (!ft_is_sorted(list_a))
	{
		if (ft_lstsize(list_a) == 2)
			sort_two(&list_a);
		if (ft_lstsize(list_a) == 3)
			sort_three(&list_a);
		if (ft_lstsize(list_a) >= 4)
			sort_turks(&list_a, &list_b);
	}
	// #endif
	return (free_data(data, numbers, &list_a, &list_b), 0);
}

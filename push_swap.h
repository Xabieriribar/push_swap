/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 08:59:53 by xiribar           #+#    #+#             */
/*   Updated: 2025/12/09 20:37:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/* MACROS                                   */
/* -------------------------------------------------------------------------- */

// Macros for TARGET_NODE
# ifndef NEXT_BIGGEST
#  define NEXT_BIGGEST 1
# endif

# ifndef NEXT_SMALLEST
#  define NEXT_SMALLEST 0
# endif

// Macros for PRINTING

# ifndef PRINT_IT
#  define PRINT_IT 4
# endif

/* -------------------------------------------------------------------------- */
/* STRUCTURES                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_stack
{
	int				number;
	int				index;
	int				cost;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_data
{
	int		argc;
	char	**argv;
	int		mode;
}	t_data;

/* -------------------------------------------------------------------------- */
/* PARSING                                   */
/* -------------------------------------------------------------------------- */

bool	ft_parse_input(t_data *data, int **numbers);
void	free_split_argv(char **argv);
int		count_the_words(char **argv);
bool	ft_is_duplicate(int **numbers, t_data *data);
bool	ft_atol_safe(char *str, int *val);

/* -------------------------------------------------------------------------- */
/* LIBFT / UTILS                                 */
/* -------------------------------------------------------------------------- */

int		ft_printf(const char *format, ...);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
long	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);

/* -------------------------------------------------------------------------- */
/* LIST UTILS                                  */
/* -------------------------------------------------------------------------- */

t_stack	*stack_new(int number);
t_stack	*stack_last(t_stack *lst);
void	stack_clear(t_stack **lst);
void	stack_add_back(t_stack **lst, t_stack *new);
void	stack_fill(t_stack **list, int *numbers, int argc);
int		stack_size(t_stack *list);

/* -------------------------------------------------------------------------- */
/* SORT ALGORITHMS                                */
/* -------------------------------------------------------------------------- */

bool	ft_is_sorted(t_stack *list);
void	sort_two(t_stack **list);
void	sort_three(t_stack **list);
void	sort_smallest(t_stack **list_a);
void	sort_turks(t_stack **list_a, t_stack **list_b);

/* -------------------------------------------------------------------------- */
/* TURK & SORT UTILS                               */
/* -------------------------------------------------------------------------- */

// Calculations & Finders
int		calculate_median(t_stack *list_a);
int		set_costs(int index_a, int index_target, int len_a, int len_b);
t_stack	*get_target_node(t_stack *list_a, t_stack *source_node, int to_find);
t_stack	*find_smallest(t_stack *list);
t_stack	*return_lowest_cost_node(t_stack *list_a);
t_stack	*find_next_biggest(t_stack *list_a, int source_number);
t_stack	*find_next_smallest(t_stack *list_b, int source_number);
t_stack	*find_cost(t_stack *list_a, int len_a, int len_b);

// Actions
void	update_indexes(t_stack **list_a, t_stack **list_b);
void	assign_target_nodes_to_a(t_stack **list_a, t_stack **list_b);
void	push_to_top(t_stack *smallest_to_push, t_stack **list_a,
			t_stack **list_b);
void	is_target_below_or_above(t_stack *target_node, t_stack **list_a,
			t_stack **list_b, int print);
void	put_biggest_in_bottom(t_stack **list);
void	from_a_to_b(t_stack **list_a, t_stack **list_b);
void	from_b_to_a(t_stack **list_a, t_stack **list_b);

// Checks
bool	last_is_biggest(t_stack *list, t_stack *last);
bool	swap_two(t_stack **list);

/* -------------------------------------------------------------------------- */
/* OPERATIONS                                  */
/* -------------------------------------------------------------------------- */

void	pa(t_stack **list_a, t_stack **list_b, int mode);
void	pb(t_stack **list_a, t_stack **list_b, int mode);

void	sa(t_stack **list, int mode);

void	ra(t_stack **list, int mode);
void	rb(t_stack **list, int mode);
void	rr(t_stack **list_a, t_stack **list_b);

void	rra(t_stack **list, int mode);
void	rrb(t_stack **list, int mode);
void	rrr(t_stack **list_a, t_stack **list_b);

#endif

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

# ifndef MAX_SIZE
#  define MAX_SIZE 10000
# endif

# ifndef MIN
#  define MIN(a, b) (((a) > (b)) ? b : a)
# endif

# ifndef MAX
#  define MAX(a, b) (((a) > (b)) ? a : b)
# endif

// Macros for TARGET_NODE
# ifndef NEXT_BIGGEST
#  define NEXT_BIGGEST 1
# endif

# ifndef NEXT_SMALLEST
#  define NEXT_SMALLEST 0
# endif

// Macros for Operations
# ifndef PUSH_A
#  define PUSH_A 2
# endif

# ifndef PUSH_B
#  define PUSH_B 3
# endif

# ifndef PRINT_IT
#  define PRINT_IT 4
# endif

/* -------------------------------------------------------------------------- */
/* STRUCTURES                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_list
{
    int             number;
    int             index;
    int             cost;
    struct s_list   *target_node;
    struct s_list   *next;
    struct s_list   *prev;
}                   t_list;

typedef struct s_data
{
    int     argc;
    char    **argv;
    int     mode;
}           t_data;

/* -------------------------------------------------------------------------- */
/* PARSING                                   */
/* -------------------------------------------------------------------------- */

bool    ft_parse_input(t_data *data, int **numbers);

/* -------------------------------------------------------------------------- */
/* LIBFT / UTILS                                 */
/* -------------------------------------------------------------------------- */

int     ft_printf(const char *format, ...);
int     ft_atoi(const char *nptr);
char    **ft_split(char const *s, char c);
char    *ft_strchr(const char *s, int c);

/* -------------------------------------------------------------------------- */
/* LIST UTILS                                  */
/* -------------------------------------------------------------------------- */

t_list  *ft_lstnew(int number, int index, t_list *target_node);
t_list  *ft_lstlast(t_list *lst);
t_list  *copy_list(t_list *list);
void    ft_lstclear(t_list **lst);
void    ft_fill_list(t_list **list, int *numbers, int argc);
void    make_list(t_list **list, int *numbers, int argc);
void    print_list(t_list *list);
int     ft_lstsize(t_list *list);

/* -------------------------------------------------------------------------- */
/* SORT ALGORITHMS                                */
/* -------------------------------------------------------------------------- */

bool    ft_is_sorted(t_list *list);
void    sort_two(t_list **list);
void    sort_three(t_list **list);
void    sort_smallest(t_list **list_a);
void    sort_turks(t_list **list_a, t_list **list_b);

/* -------------------------------------------------------------------------- */
/* TURK & SORT UTILS                               */
/* -------------------------------------------------------------------------- */

// Calculations & Finders
int     calculate_median(t_list *list_a);
int     set_costs(int index_a, int index_target, int len_a, int len_b);
t_list  *get_target_node(t_list *list_a, t_list *source_node, int to_find);
t_list  *find_smallest(t_list *list);
t_list  *return_lowest_cost_node(t_list *list_a);
t_list  *find_next_biggest(t_list *list_a, int source_number);
t_list  *find_next_smallest(t_list *list_b, int source_number);
t_list  *find_cost(t_list *list_a, int len_a, int len_b);

// Actions
void    update_indexes(t_list **list_a, t_list **list_b);
void    assign_target_nodes_to_a(t_list **list_a, t_list **list_b);
void    push_to_top(t_list *smallest_to_push, t_list **list_a, t_list **list_b);
void    is_target_below_or_above(t_list *target_node, t_list **list_a, t_list **list_b, int mode, int print);
void    put_biggest_in_bottom(t_list **list);
void    from_a_to_b(t_list **list_a, t_list **list_b);
void    from_b_to_a(t_list **list_a, t_list **list_b);

// Checks
bool    last_is_biggest(t_list *list, t_list *last);
bool    swap_two(t_list **list);

/* -------------------------------------------------------------------------- */
/* OPERATIONS                                  */
/* -------------------------------------------------------------------------- */

void    pa(t_list **list_a, t_list **list_b, int mode);
void    pb(t_list **list_a, t_list **list_b, int mode);

void    sa(t_list **list, int mode);
// Added sb just in case, assuming symmetry
// Note: You didn't have 'sb' or 'ss' in your original list, ensure they exist if needed.

void    ra(t_list **list, int mode);
void    rb(t_list **list, int mode);
void    rr(t_list **list_a, t_list **list_b);

void    rra(t_list **list, int mode);
void    rrb(t_list **list, int mode);
void    rrr(t_list **list_a, t_list **list_b);

#endif
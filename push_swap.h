#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "stdio.h"

#ifndef MAX_SIZE
#define MAX_SIZE 10000
#endif

#ifndef MIN
#define MIN(a, b) (((a) > (b)) ? b : a)
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? a : b);
#endif

//MACROS FOR TARGET_NODE
#ifndef NEXT_BIGGEST
#define NEXT_BIGGEST 1
#endif

#ifndef NEXT_SMALLEST
#define NEXT_SMALLEST 0
#endif


#ifndef PUSH_A
#define PUSH_A 2
#endif

#ifndef PUSH_B
#define PUSH_B 3
#endif

#ifndef PRINT_IT
#define PRINT_IT 4
#endif
typedef struct s_list
{
    int number;
    int index;
    int cost;
    struct s_list *target_node;
    struct s_list *next;
    struct s_list *prev;
} t_list;

typedef struct s_data
{
    int argc;
    char **argv;
    int mode;
} t_data;
bool    ft_parse_input(t_data *data, int **numbers);
void    make_list(t_list **list, int *numbers, int argc);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
bool    ft_is_sorted(t_list *list);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *nptr);
int	ft_printf(const char *format, ...);
//LISTS
t_list *ft_lstlast(t_list *lst);
int ft_lstsize(t_list *list);
t_list *ft_lstnew(int number, int index, t_list *target_node);
void print_list(t_list *list);
t_list *copy_list(t_list *list);
void	ft_lstclear(t_list **lst);
void    ft_fill_list(t_list **list, int *numbers, int argc);
//SORTS
bool    ft_is_sorted(t_list *list);
void    sort_smallest(t_list **list_a);
void    sort_two(t_list **list);
void    sort_three(t_list **list);
void    sort_turks(t_list **list_a, t_list **list_b);
//SORT UTILS
bool    last_is_biggest(t_list *list, t_list *last);
void    put_biggest_in_bottom(t_list **list);
bool    swap_two(t_list **list);
//TURK UTILS
void    update_indexes(t_list **list_a, t_list **list_b);
t_list *get_target_node(t_list *list_a, t_list *source_node, int to_find);
int calculate_median(t_list *list_a);
t_list *find_smallest(t_list *list);
void    sort_smallest(t_list **list_a);
void    from_b_to_a(t_list **list_a, t_list **list_b);
void    from_a_to_b(t_list **list_a, t_list **list_b);
t_list *return_lowest_cost_node(t_list *list_a);
int     set_costs(int index_a, int index_target, int len_a, int len_b);
void    assign_target_nodes_to_a(t_list **list_a, t_list **list_b);
void    push_to_top(t_list *smallest_to_push, t_list **list_a, t_list **list_b);
void    is_target_below_or_above(t_list *target_node, t_list **list_a, t_list **list_b, int mode, int print);
//OPERATIONS
void    sa(t_list **list, int mode);
void    rra(t_list **list, int mode);
void    ra(t_list **list, int mode);
void    pb(t_list **list_a, t_list **list_b, int mode);
void    pa(t_list **list_a, t_list **list_b, int mode);
void rr(t_list **list_a, t_list **list_b);
void rrr(t_list **list_a, t_list **list_b);
void    rrb(t_list **list, int mode);
void    rb(t_list **list, int mode);
//FIND FUNCTIONS
t_list *find_next_biggest(t_list *list_a, int source_number);
t_list *find_next_smallest(t_list *list_b, int source_number);
t_list *find_cost(t_list *list_a, int len_a, int len_b);
#endif

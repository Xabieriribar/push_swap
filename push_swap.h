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
typedef struct s_list_a
{
    int number;
    int index;
    int cost;
    struct s_list_a *target_node;
    struct s_list_a *next;
    struct s_list_a *prev;
} t_list_a;

typedef struct s_data
{
    int argc;
    char **argv;
    int mode;
} t_data;
bool    ft_parse_input(t_data *data, int **numbers);
void    make_list(t_list_a **list, int *numbers, int argc);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
bool    ft_is_sorted(t_list_a *list);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *nptr);
int	ft_printf(const char *format, ...);
//LISTS
t_list_a *ft_lstlast(t_list_a *list);
int ft_lstsize(t_list_a *list);
t_list_a *ft_lstnew(int number, int index, t_list_a *target_node);
void print_list(t_list_a *list);
t_list_a *copy_list(t_list_a *list);
void	ft_lstclear(t_list_a **lst);
//SORTS
void    sort_two(t_list_a **list);
void    sort_three(t_list_a **list);
void    sort_turks(t_list_a **list_a, t_list_a **list_b);
//SORT UTILS
bool    last_is_biggest(t_list_a *list, t_list_a *last);
void    put_biggest_in_bottom(t_list_a **list);
bool    swap_two(t_list_a **list);
//TURK UTILS
void    update_indexes(t_list_a **list_a, t_list_a **list_b);
t_list_a *get_target_node(t_list_a *list_a, t_list_a *source_node, int to_find);
int calculate_median(t_list_a *list_a);
t_list_a *find_smallest(t_list_a *list);
void    sort_smallest(t_list_a **list_a);
void    from_b_to_a(t_list_a **list_a, t_list_a **list_b);
void    from_a_to_b(t_list_a **list_a, t_list_a **list_b);
t_list_a *return_lowest_cost_node(t_list_a *list_a);
//OPERATIONS
void    sa(t_list_a **list, int mode);
void    rra(t_list_a **list, int mode);
void    ra(t_list_a **list, int mode);
void    pb(t_list_a **list_a, t_list_a **list_b, int mode);
void    pa(t_list_a **list_a, t_list_a **list_b, int mode);
void rr(t_list_a **list_a, t_list_a **list_b);
void rrr(t_list_a **list_a, t_list_a **list_b);
void    rrb(t_list_a **list, int mode);
void    rb(t_list_a **list, int mode);
//FIND FUNCTIONS
t_list_a *find_next_biggest(t_list_a *list_a, int source_number);
t_list_a *find_next_smallest(t_list_a *list_b, int source_number);
t_list_a *find_node_with_smallest_cost(t_list_a **list_a, t_list_a **list_b);
#endif

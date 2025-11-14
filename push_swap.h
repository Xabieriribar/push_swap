#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "stdio.h"

#ifndef MAX_SIZE
#define MAX_SIZE 10000
#endif

typedef struct s_list_a
{
    int number;
    int index;
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
size_t ft_lstsize(t_list_a *list);
t_list_a *ft_lstnew(int number, int index);
//SORTS
void    sort_two(t_list_a **list);
void    sort_three(t_list_a **list);
void    sort_turks(t_list_a **list_a, t_list_a **list_b);
//OPERATIONS
void    sa(t_list_a **list);
void    rra(t_list_a **list);
void    ra(t_list_a **list);
void    pb(t_list_a **list_a, t_list_a **list_b);

#endif


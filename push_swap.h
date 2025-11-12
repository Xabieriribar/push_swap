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

typedef struct s_operations
{
    char *operation_list[3];
    int index;
} t_operations;

bool    ft_parse_input(int argc, char **argv, int **numbers);
void    make_list(t_list_a **list, int *numbers, size_t *lstsize, int argc);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
bool    ft_is_sorted(t_list_a *list);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *nptr);
//LISTS
t_list_a *ft_lstlast(t_list_a *list);

//SORTS

void    sort_three(t_list_a **list, t_operations *operations);
//OPERATIONS
void    sa(t_list_a **list, t_operations *operations);
void    rra(t_list_a **list, t_operations *operations);
void    ra(t_list_a **list, t_operations *operations);
void    sort_two(t_list_a **list, t_operations *operations);
#endif


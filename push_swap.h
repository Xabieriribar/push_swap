#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdbool.h>
#include <stdlib.h>
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

typedef struct s_list_b
{
    int number;
    int index;
    struct s_list_a *next;
    struct s_list_a *prev;
} t_list_b;

bool    ft_parse_input(int argc, char **argv, int **numbers);
void    make_list(t_list_a **list, int *numbers);
int	ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *nptr);
#endif


#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdbool.h>

typedef struct s_nums
{
    int *nums;
} t_nums;

bool    ft_parse_input(int argc, char **argv, t_nums *nums);
char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *nptr);
#endif


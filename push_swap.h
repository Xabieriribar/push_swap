#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdbool.h>
#include <stdlib.h>
#include "stdio.h"

#ifndef MAX_SIZE
#define MAX_SIZE 10000
#endif

bool    ft_parse_input(int argc, char **argv, int **numbers);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int	ft_atoi(const char *nptr);
#endif


#include "push_swap.h"

bool    ft_parse_input(int argc, char **argv, t_nums *nums)
{
    char **argv_p;
    int  index;


    if (argc == 1)
        return (false);
    argv_p = argv;
    *argv++;
    while (**argv)
    {
        nums->nums = ft_atoi(*argv);
        if (!nums->nums);
            return (false);
        *argv++;
    }
    index = 0;
    while (*argv_p[index]) 
    {
        index = *argv_p;
        while (*argv_p[index])
        {
            if (ft_strchr(*argv_p, *argv_p[index]))
                return (false);
            
        }
        *argv_p++;
    }
    return (true)
}
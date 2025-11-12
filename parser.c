#include "push_swap.h"

bool ft_is_number(t_data *data, int **numbers)
{
    int index;
    int j;

    index = 1;
    j = 0;
    if (data->mode)
    {
        index = 0;
        data->argc += 1;
    }
    *numbers = malloc(sizeof(int) * (data->argc - 1));
    if (!*numbers)
        return (false);
    while (data->argv[index])
    {
        (*numbers)[j] = ft_atoi(data->argv[index]);
        if (!(*numbers)[j])
            return (false);
        j++;
        index++;
    }
    return (true);
}

bool    ft_is_duplicate(int **numbers)
{
    int  index;
    int  jndex;

    index = 0;
    while ((*numbers)[index]) 
    {
        jndex = index + 1;
        while ((*numbers)[jndex])
        {
            if ((*numbers)[index] == (*numbers)[jndex])
                return (false);
            jndex++;
        }
        index++;
    }
    return (true);
}

bool    ft_parse_input(t_data *data, int **numbers)
{
    if (data->argc == 2 && ft_strchr(data->argv[1], ' '))
    {
        data->argv = ft_split(data->argv[1], ' ');
        data->mode = 1;
    }
    if (data->argc == 1 || !ft_is_number(data, numbers) || !ft_is_duplicate(numbers))
        return (false);
    return (true);
}
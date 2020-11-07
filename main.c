#include "minishell.h"

int main(int ac, char **argv)
{
    char *line;
    get_next_line(0, &line);
    ft_printf("Success : %s !\n",line);
    return (0);
}
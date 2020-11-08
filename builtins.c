#include "minishell.h"

void    init_builtins()
{
    int     i;
    char    **tmp;

    i = 0;
    if (!(tmp = ft_split("echo,cd,pwd,export,unset,env,exit", ',')))
        return ;
    while (i < 7)
    {
        g_builtins_str[i] = ft_strdup(tmp[i]);
        free(tmp[i++]);
    }
    free(tmp);
    g_builtins_str[i] = NULL;
}
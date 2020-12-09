#include "minishell.h"

void    signal_handler(int signal)
{
    char    s[1024];

    getcwd(s, 1000);
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
        ft_printf("\033[0;32m");
        ft_printf("\n%s", s);
        ft_putstr_fd(" $ ", STDOUT);
        ft_printf("\033[0m");
        signal_c = 1;
    }
    if (signal == SIGQUIT)
    {
        // doesn't seem to work
        //g_child = getpid();
        if (kill(g_child, 0) == 0)
        {
            ft_printf("%d\n", g_child);
            kill(g_child, SIGQUIT);
        }
    }
}

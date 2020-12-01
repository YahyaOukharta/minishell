#include "minishell.h"

void    signal_handler(int signal)
{
    char    s[1024];

    getcwd(s, 1000);
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
        ft_printf("\n%s ", s);
        signal_c = 1;
    }
    if (signal == SIGQUIT)
    {
        // get pid 
        kill(g_child, SIGQUIT);
    }
}

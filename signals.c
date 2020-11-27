#include "minishell.h"

void    signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
        ft_putstr_fd("\n$> ", STDOUT);
        signal_c = 1;
    }
    if (signal == SIGQUIT)
    {
        // get pid 
        kill(g_child, SIGQUIT);
    }
}
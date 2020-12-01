#include "minishell.h"

void    signal_handler(int signal)
{
    char    s[1024];

    getcwd(s, 1000);
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
        ft_putchar_fd('\n', STDOUT);
        ft_putstr_fd(s, STDOUT);
        ft_putchar_fd(' ', STDOUT);
        signal_c = 1;
    }
    if (signal == SIGQUIT)
    {
        // get pid 
        kill(g_child, SIGQUIT);
    }
}

#include "minishell.h"

/*
    The primary problem is that if the signal interrupts malloc()
    or some similar function, the internal state may be temporarily
    inconsistent while it is moving blocks of memory
    between the free and used list, or other similar operations.
    If the code in the signal handler calls a function that then invokes malloc(),
    this may completely wreck the memory management.
*/

void    signal_handler(int signal)
{
    char    s[1024];

    getcwd(s, 1000);
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
        write(STDOUT, "\033[0;32m\n", ft_strlen("\033[0;32m\n"));
        write(STDOUT, s, ft_strlen(s));
        write(STDOUT, " $ ", ft_strlen(" $ "));
        write(STDOUT, "\033[0m", ft_strlen("\033[0m"));
        signal_c = 1;
    }
    if (signal == SIGQUIT)
    {
        /*if (kill(g_child, 0) == 0)
            kill(g_child, SIGQUIT);*/
    }
}

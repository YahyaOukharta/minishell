#include "minishell.h"

void    signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        // print prompt and set a var to print /r if needed
    }
    if (signal == SIGQUIT)
    {
        // get pid 
        //kill pid
    }
}
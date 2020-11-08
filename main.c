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

int         ft_prompt(char *msg, char **line)
{
    ft_putstr_fd(msg, STDOUT);
    ft_putchar_fd(' ', STDOUT);
    return (get_next_line(STDIN, line));
}

// to do list xD 3yiit

int         ft_get_info(char *cmd)
{
    return (1);
}

int         ft_parser(char *line)
{
    char    *cmd;

    // quotes
    // pipes
    // redirection
    if (!(cmd = check_syntax(line))) // still need to free 
    {
        ft_putstr_fd("THIS SHELL ISN'T FOR YOU STUPID LINE\n", STDOUT);
        // keep the loop for the moment 
        return (2);
    }
    // getting all info needed before exec 
    return (ft_get_info(cmd));
}

void        ft_minishell(char **env)
{
    char    *line;
    char    cwd[1024];
    int     rt;

    rt = 0;
    line = NULL;
    init_environment(env);
    init_builtins();
    // ctrl + c
    signal(SIGINT, signal_handler);
    // ctrl + d 
    signal(SIGQUIT, signal_handler);
    // main loop
    status = 1;
    while (status) // status is global var defined in header
    {
        rt = ft_prompt(getcwd(cwd, 1024), &line);
        if (rt == 0 || rt == -1) // gnl return 0 when there is no \n (EOF)
        {
            if (line == NULL)
                exit(1);
        }
        status = ft_parser(line);
        ft_putstr_fd(line, 1);
    }
    // char *line;
    // get_next_line(0, &line);
    // ft_printf("Success : %s !\n",line);
}

int     main(int ac, char **argv, char **env)
{
    if (ac == 1)
        ft_minishell(env);
    else
        ft_printf("Usage : ./minishell\n");
    return (0);
}
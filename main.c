#include "minishell.h"

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
    //signal(SIGINT, signal_handler);
    // ctrl + d 
    //signal(SIGQUIT, signal_handler);
    // main loop


    g_status = 1;

    t_pipeline **parsed_line;


    while (g_status) // status is global var defined in header
    {
        rt = ft_prompt("$> ", &line);
        if (rt == 0 || rt == -1) // gnl return 0 when there is no \n (EOF)
            if (line == NULL)
                exit(1);

        //g_status = ft_parser(line);
        parsed_line = mini_parser(line);
        print_parsed_line(parsed_line);
        //ft_printf("cmd = %s\n", line);
    }
}

int     main(int ac, char **argv, char **env)
{
    if (ac == 1)
        ft_minishell(env);
    else
        ft_printf("Usage : ./minishell\n");
    return (0);
}
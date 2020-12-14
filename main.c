#include "minishell.h"

int         ft_prompt(char *msg, char **line)
{
    if (signal_c == 1)
        ft_putchar_fd('\r', STDOUT);
    if (signal_d == 1)
    {
        ft_putstr_fd(msg, STDOUT);
        ft_putstr_fd(" $ ", STDOUT);
    }
    ft_printf("\033[0m");
    return (get_next_line(STDIN, line));
}

void        ft_minishell(char **env)
{
    char    *line;
    char    cwd[1024];
    int     rt;
    int     i;
    char    *checked_line;

    rt = 0;
    init_environment(env);
    init_builtins();
    // ctrl + c
    signal(SIGINT, signal_handler);
    // ctrl + '\'
    signal(SIGQUIT, signal_handler);
    // main loop


    g_status = 0;
    signal_c = 0;
    signal_d = 1;
    t_pipeline **parsed_line;
    // Cntrl D problem when cmd is not found 
    while (g_status != -1) // status is global var defined in header
    {
        g_child = MAX_INT;
        line = NULL;
        getcwd(cwd, 1000);
        ft_printf("\033[0;32m");
        rt = ft_prompt(cwd, &line);
        if (rt == 0) // gnl return 0 when there is no \n (EOF)
        {
            if (ft_strlen(line))
            {
                free(line);
                line = NULL;
                signal_d = 0;
                continue ;
            }
            else
                exit(1);
        }
        signal_d = 1;
        if (!(checked_line = check_line(line)))
        {
            free(line);
            continue ;
        }
        parsed_line = parser(checked_line);
        print_parsed_line(parsed_line);

        i = 0;
        while (parsed_line[i])
        {
            g_status = execute_pipeline(parsed_line[i]);
            i++;
        }
        free(line);
        line = NULL;
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

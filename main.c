#include "minishell.h"

int         ft_prompt(char *msg, char **line)
{
    if (signal_c == 1)
        ft_putchar_fd('\r', STDOUT);
    if (signal_d == 1)
    {
        ft_putstr_fd(msg, STDOUT);
        ft_putchar_fd(' ', STDOUT);
    }
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
    int     i;

    rt = 0;
    line = NULL;
    init_environment(env);
    init_builtins();
    // ctrl + c
    signal(SIGINT, signal_handler);
    // ctrl + d 
    signal(SIGQUIT, signal_handler);
    // main loop


    g_status = 0;

    t_pipeline **parsed_line;

    signal_c = 0;
    signal_d = 1;
    while (g_status != -1) // status is global var defined in header
    {
        signal_c = 0;
        rt = ft_prompt("$> ", &line);
        if (rt == 0) // gnl return 0 when there is no \n (EOF)
        {
            if (ft_strlen(line) == 0)
                exit(1);
            else
                signal_d = 0;
            continue ;
        }
        signal_d = 1;
        //g_status = ft_parser(line);
        parsed_line = mini_parser(line);
        print_parsed_line(parsed_line);

        //execute_command(0, 1, parsed_line[0]->cmds[0]->tokens);
        //redirect_inputs(parsed_line[0]->cmds[0]->tokens, 1,0,parsed_line[0]->cmds[0]->input_files);
        //redirect_outputs(parsed_line[0]->cmds[0],0,1);
        //execute_pipeline(parsed_line[0]);
        i = 0;
        while (parsed_line[i])
        {
            g_status = execute_pipeline(parsed_line[i]);
            i++;
        }
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

#include "minishell.h"

void    redirect_in_out(int in, int out)
{
    if (in != 0)
    {
        dup2(in, 0);
        //close(in);
    }
    if (out != 1)
    {
        dup2(out, 1);
        //close(out);
    }
}

int		new_process(int in, int out, char **cmd, int *status)
{
    int pid;
    char *path;

    pid = fork(); // missing error handling
    if (pid == 0)
    {
        if (!find_file_in_path(&path, cmd[0]))
        {
            ft_printf("minishell: command not found: %s\n", cmd[0]);
            return (127);
        }
        redirect_in_out(in, out);
        if ((execve(path, cmd, get_env_tab()) == -1))
        {
            ft_printf("minishell: permission denied: %s\n", cmd[0]);
            return (126);
        }
    }
    else
        pid = wait(status);
    return (*status);
}

int		new_builtin_process(int in, int out,char **argv, int(*builtin)(int,int, char **))
{
    int pid;
    char *path;
    int ret;

    if (string_equal(argv[0], "env") ||
        string_equal(argv[0], "pwd") ||
        string_equal(argv[0], "echo"))
    {
        pid = fork(); // missing error handling
        if (pid == 0)	
        {
            ret = builtin(in, out, argv);
            exit(ret);
        }
        else
            pid = wait(&ret);
    }
    else
        ret = builtin(in, out, argv);
    return (ret);
}

int		execute_command(int in, int out, char **argv)
{
	char **cmd;
	pid_t child_pid;
	int index;
	char *path;
	
	if (tab_len(argv))
	{
		if ((index = index_of_in_tab(argv[0], g_builtins_str)) > -1)
			g_status = new_builtin_process(in, out, argv, g_builtins[index]);
		else
			g_status = new_process(in, out, argv, &g_status);
	}
	return (g_status);
}


#include "minishell.h"

void	redirect_in_out(int in, int out)
{
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
}

int		new_process(int in, int out, char **cmd, int *status)
{
	int		pid;
	char	*path;

	if (!find_file_in_path(&path, cmd[0]))
	{
		ft_printf("minishell: command not found: %s\n", cmd[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		redirect_in_out(in, out);
		if ((execve(path, cmd, get_env_tab()) == -1))
		{
			ft_printf("minishell: permission denied: %s\n", cmd[0]);
			return (126);
		}
	}
	else
	{
		g_child = pid;
		pid = waitpid(-1, status, WUNTRACED| WCONTINUED);
	}
	return (*status);
}

int		new_builtin_process(int in, int out,
	char **av, int (*b)(int, int, char **))
{
	int		pid;
	char	*path;
	int		ret;

	if (string_equal(av[0], "env") ||
		string_equal(av[0], "pwd") ||
		string_equal(av[0], "echo") ||
		(string_equal(av[0], "exit") && out != 1))
	{
		pid = fork();
		if (pid == 0)
		{
			ret = b(in, out, av);
			exit(ret);
		}
		else
			pid = wait(&ret);
	}
	else
		ret = b(in, out, av);
	return (ret);
}

int		execute_command(int in, int out, char **argv)
{
	char	**cmd;
	pid_t	child_pid;
	int		index;
	char	*path;

	if (tab_len(argv))
	{
		if ((index = index_of_in_tab(argv[0], g_builtins_str)) > -1)
			g_status = new_builtin_process(in, out, argv, g_builtins[index]);
		else
			g_status = new_process(in, out, argv, &g_status);
	}
	return (g_status);
}

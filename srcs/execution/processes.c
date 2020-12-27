/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:49:48 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:49:54 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int *g_children;

void queue_pid(int pid)
{
	int i;

	i = 0;
	g_child = pid;
	while (g_children[i] != 0)
		i++;
	g_children[i] = pid;
}

void	redirect_in_out(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
		dup2(out, 1);
}

int		new_process(int in, int out, char **cmd, int *status)
{
	int		pid;
	char	*path;

	path = NULL;
	if (!find_file_in_path(&path, cmd[0]))
	{
		ft_printf("minishell: command not found: %s\n", cmd[0]);
		free(path);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("fork failed\n");
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		redirect_in_out(in, out);
		if ((execve(path, cmd, get_env_tab()) == -1))
		{
			ft_printf("minishell: permission denied: %s\n", cmd[0]);
			free(path);
			return (126);
		}
		exit(EXIT_SUCCESS);
	}
	else
		queue_pid(pid);
	free(path);
	return (*status);
}

int		new_builtin_process(int in, int out,
	char **av, int (*b)(int, int, char **))
{
	int		pid;
	int		ret;

	if (string_equal(av[0], "env") ||
		string_equal(av[0], "pwd") ||
		string_equal(av[0], "echo") ||
		(string_equal(av[0], "exit") && out != 1))
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf("fork failed\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			ret = b(in, out, av);
			exit(ret);
		}
		else
			queue_pid(pid);
	}
	else
		ret = b(in, out, av);
	return (g_status);
}

int		execute_command(int in, int out, char **argv)
{
	int		index;

	if (tab_len(argv))
	{
		if ((index = index_of_in_tab(argv[0], g_builtins_str)) > -1)
			g_status = new_builtin_process(in, out, argv, g_builtins[index]);
		else
			g_status = new_process(in, out, argv, &g_status);
	}
	return (g_status);
}

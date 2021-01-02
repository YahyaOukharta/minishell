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

int		new_process(int in, int out, char **cmd, int *status)
{
	int		pid;

	if ((pid = fork()) == -1)
	{
		ft_printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		find_execute_binary(cmd, in, out);
	else
		queue_pid(pid);
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
		g_status = b(in, out, av);
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

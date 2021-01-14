/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:49:48 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/14 17:32:09 by malaoui          ###   ########.fr       */
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
		(string_equal(av[0], "exit") && out != 1) ||
		(string_equal(av[0], "export") && (out != 1 || in != 0)))
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
	char	*path_info;
	t_env	*path;

	path_info = NULL;
	path = env_with_key("PATH");
	path_info = ft_strrchr(path->value, ':') == NULL ? path->value : ft_strrchr(path->value, ':') + 1;
	if (tab_len(argv))
	{
		//if (ft_strncmp(*argv, "export", 6) && ft_strncmp(*argv, "unset", 5) 
		set_env("_", ft_strjoin(path_info, ft_strjoin("/", *argv)));
		if ((index = index_of_in_tab(argv[0], g_builtins_str)) > -1)
			g_status = new_builtin_process(in, out, argv, g_builtins[index]);
		else
			g_status = new_process(in, out, argv, &g_status);
	}
	return (g_status);
}

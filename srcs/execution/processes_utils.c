/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:49:48 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:49:54 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int *g_children;

void	queue_pid(int pid)
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

int		find_execute_binary(char **cmd, int in, int out)
{
	char	*path;

	if (!find_file_in_path(&path, cmd[0]))
	{
		ft_printf("minishell: command not found: %s\n", cmd[0]);
		exit(127);
	}
	redirect_in_out(in, out);
	if ((execve(path, cmd, get_env_tab()) == -1))
	{
		ft_printf("minishell: permission denied: %s\n", cmd[0]);
		free(path);
		exit(126);
	}
	exit(EXIT_SUCCESS);
}

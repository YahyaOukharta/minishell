/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:49:48 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/12 15:03:35 by malaoui          ###   ########.fr       */
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

int is_regular_file(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int is_link_file(const char *path)
{
    struct stat path_stat;

    return (!lstat(path, &path_stat));
}

int is_exe_usr(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return ((S_IXUSR) & path_stat.st_mode);
}

int is_exe_grp(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return ((S_IXGRP) & path_stat.st_mode);
}

int is_exe_oth(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return ((S_IXOTH) & path_stat.st_mode);
}

int		find_execute_binary(char **cmd, int in, int out)
{
	char	*path;

	if (!find_file_in_path(&path, cmd[0]))
	{
		ft_printf("minishell: %s: command not found\n", cmd[0]);
		exit(127);
	}
	redirect_in_out(in, out);
	if ((execve(path, cmd, get_env_tab()) == -1))
	{
		if (errno == 13 && is_regular_file(path))
			ft_printf("minishell: %s: Permission denied\n", cmd[0], errno);
		else if (errno == 13)
			ft_printf("minishell: %s: is a directory\n", cmd[0], errno);
		else if (errno == 8)
		{
			if (!is_exe_usr(path) && is_exe_oth(path) && is_exe_grp(path))
			{
				ft_printf("minishell: %s: Permission denied\n", cmd[0], errno);
				exit((int)free_and_return((void *)path, (void *)126));
			}
			exit((int)free_and_return((void *)path, (void *)0));
		}
		exit(errno == 2 ? 127 : 126);
	}
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:49:48 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/14 16:59:34 by malaoui          ###   ########.fr       */
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

int		execve_error_handling(char *cmd, char *path, int err)
{
	if (err == 13 && is_regular_file(path))
		ft_printf("minishell: %s: Permission denied\n", path, err);
	else if (err == 13)
		ft_printf("minishell: %s: is a directory\n", path, err);
	else if (err == 8)
	{
		if (!is_exe_usr(path) && (is_exe_oth(path) && is_exe_grp(path)))
		{
			ft_printf("minishell: %s: Permission denied\n", cmd, err);
			return ((int)free_and_return((void *)path, (void *)126));
		}
		return ((int)free_and_return((void *)path, (void *)0));
	}
	return (err == 2 ? 127 : 126);
}

int		find_execute_binary(char **cmd, int in, int out)
{
	char	*path;
	t_env	*env;

	if (!find_file_in_path(&path, cmd[0]))
	{
		env = env_with_key("PATH");
		if (env != NULL && ft_strlen(env->value))
			ft_printf("minishell: %s: command not found\n", cmd[0]);
		else
			ft_printf("minishell: %s: No such file or directory\n", cmd[0]);
		exit(127);
	}
	redirect_in_out(in, out);
	set_env("_", path);
	if ((execve(path, cmd, get_env_tab()) == -1))
		exit(execve_error_handling(cmd[0], path, errno));
	exit(EXIT_SUCCESS);
}

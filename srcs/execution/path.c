/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:03:24 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/12 15:03:35 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	**get_parsed_path(void)
{
	t_env *env;

	if (!g_env)
		return (0);
	env = env_with_key("PATH");
	if (env != NULL)
		return (ft_split(env->value, ':'));
	return (0);
}

int		rel_abs_path(char *cmd, char **str)
{
	struct stat	buf;

	if (!stat(cmd, &buf))
	{
		*str = ft_strdup(cmd);
		return (1);
	}
	else
	{
		ft_printf("minishell: %s: No such file or directory\n", cmd);
		return (126);
	}
}

int		loop_over_path(char *cmd, char **path, char **str)
{
	int			i;
	struct stat	buf;

	i = 0;
	while (path && path[i])
	{
		*str = ft_strjoin_va(3, path[i++], "/", cmd);
		if (!stat(*str, &buf))
		{
			free_s_tab(path);
			return (1);
		}
		free(*str);
	}
	return (0);
}

int		find_file_in_path(char **str, char *cmd)
{
	char		**path;
	int			i;
	struct stat	buf;
	char		s[1000];

	i = 0;
	if (!ft_strlen(cmd))
		return (0);
	get_cwd(s, 999);
	if (ft_strchr(cmd, '/'))
		return (rel_abs_path(cmd, str));
	path = get_parsed_path();
	if (!stat(ft_strjoin_va(3, s, "/", cmd), &buf)
		&& path && !tab_len(path))
	{
		*str = ft_strdup(cmd);
		return (1);
	}
	if (loop_over_path(cmd, path, str))
		return (1);
	*str = NULL;
	return (free_s_tab(path));
}

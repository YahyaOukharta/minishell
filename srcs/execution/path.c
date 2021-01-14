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

int		find_file_in_path(char **str, char *cmd)
{
	char		**path;
	int			i;
	struct stat	buf;
	t_env		*e;

	i = 0;
	e = env_with_key("PATH");
	if (!ft_strlen(cmd))
		return (0);
	char s[1000];
	ft_bzero(s, 1000);
	getcwd(s, 999);
	if (ft_strchr(cmd, '/'))
	{
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
	else if (!stat(ft_strjoin_va(3, s, "/", cmd), &buf)
		&& e && !tab_len(ft_split(e->value, ':')))
	{
		*str = ft_strdup(cmd);
		return (1);
	}
	if (!(path = get_parsed_path()))
		return (0);
	while (path[i])
	{
		*str = ft_strjoin_va(3, path[i++], "/", cmd);
		if (!stat(*str, &buf))
		{
			free_s_tab(path);
			return (1);
		}
		free(*str);
	}
	*str = NULL;
	return (free_s_tab(path));
}

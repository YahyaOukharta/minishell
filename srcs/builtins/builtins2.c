/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:02:51 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:51:30 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(int in, int out, char **argv)
{
	t_env	*env;

	if (tab_len(argv) != 1)
	{
		ft_printf("env: too many arguments\n");
		return (1);
	}
	redirect_in_out(in, out);
	env = g_env;
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	export_env(void)
{
	t_env	*t;

	t = g_env;
	while (t != NULL)
	{
		ft_printf("export %s=%s\n", t->key, t->value);
		t = t->next;
	}
}

int		builtin_export(int in, int out, char **argv)
{
	char	**tab;
	int		i;

	(void)in;
	(void)out;
	if (tab_len(argv) > 1)
	{
		i = 1;
		while (argv[i])
		{
			tab = ft_split(argv[i], '=');
			if (tab_len(tab) == 2)
				set_env(tab[0], tab[1]);
			if (tab_len(tab) == 1 && argv[i][ft_strlen(argv[i]) - 1] == '=')
				set_env(tab[0], ft_strdup(""));
			//free_s_tab(tab);
			i++;
		}
	}
	else if (tab_len(argv) == 1)
		export_env();
	return (0);
}

int		builtin_unset(int in, int out, char **argv)
{
	char	**tab;
	int		i;

	if (tab_len(argv) > 1)
	{
		redirect_in_out(in, out);
		i = 1;
		while (argv[i])
		{
			tab = ft_split(argv[i], '=');
			if (tab_len(tab) == 1)
				unset_env(tab[0]);
			free_s_tab(tab);
			i++;
		}
	}
	return (0);
}

int		builtin_exit(int in, int out, char **argv)
{
	(void)in;
	(void)out;
	g_return = (tab_len(argv) > 1 ? ft_atoi(argv[1]) : 0);
	return (-1);
}

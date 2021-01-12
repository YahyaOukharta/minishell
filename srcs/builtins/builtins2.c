/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:02:51 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/30 15:22:04 by malaoui          ###   ########.fr       */
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

int		is_special(char c)
{
	return (ft_strchr("$\\\"", c));
}

void	export_env(void)
{
	t_env	*env;
	int		i;

	env = g_env;
	while (env != NULL)
	{
		ft_printf("declare -x %s=\"", env->key);
		i = 0;
		while (i < ft_strlen(env->value))
		{
			if (is_special(env->value[i]))
				write(1, "\\", 1);
			write(1, env->value + i, 1);
			i++;
		}
		ft_printf("\"\n");
		env = env->next;
	}
}

int		export_helper(char *s)
{
	char	*eq;
	int		j;

	if ((eq = ft_strchr(s, '=')))
	{
		*eq = '\0';
		j = 0;
		while (ft_isalnum(s[j]))
			j++;
		if (s[j] == '\0')
			set_env(ft_strdup(s), ft_strdup(eq + 1));
		else
		{
			ft_printf("export: not a valid identifier\n");
			return (0);
		}
	}
	return (1);
}

int		builtin_export(int in, int out, char **argv)
{
	int		i;

	(void)in;
	(void)out;
	if (tab_len(argv) > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (!export_helper(argv[i]))
				return (1);
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

	(void)in;
	(void)out;
	if (tab_len(argv) > 1)
	{
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

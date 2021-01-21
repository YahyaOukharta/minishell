/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:02:51 by youkhart          #+#    #+#             */
/*   Updated: 2021/01/21 10:10:59 by malaoui          ###   ########.fr       */
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
		if (ft_strlen(env->value) != 0)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	export_env(void)
{
	t_env	*env;
	size_t	i;

	env = g_env;
	while (env != NULL)
	{
		if (!ft_strncmp(env->key, "_", max_v(1, ft_strlen(env->value))))
		{
			i++;
			env = env->next;
			continue;
		}
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

	j = 0;
	while (ft_isalnum(s[j]) || s[j] == '_')
		j++;
	if ((eq = ft_strchr(s, '=')))
	{
		if (s[j] == '=' && !ft_isdigit(s[0]))
			set_env(ft_substr(s, 0, j), ft_strdup(eq + 1));
		else
			j = -1;
	}
	else
	{
		if (ft_strlen(s) != 0 && s[j] == '\0' && !ft_isdigit(s[0]))
			set_env(ft_substr(s, 0, j), ft_strdup(""));
		else
			j = -1;
	}
	if (j == -1)
		ft_printf("minishell: export: `%s': not a valid identifier\n", s);
	return (j == -1 ? 0 : 1);
}

int		builtin_export(int in, int out, char **argv)
{
	int		i;
	int		flag;

	(void)in;
	(void)out;
	flag = 0;
	if (tab_len(argv) > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (!export_helper(argv[i]))
				flag = 1;
			i++;
		}
	}
	else if (tab_len(argv) == 1)
		export_env();
	return (flag);
}

int		builtin_unset(int in, int out, char **argv)
{
	char	**tab;
	int		i;
	int		flag;

	(void)in;
	(void)out;
	flag = 0;
	if (tab_len(argv) > 1)
	{
		i = 0;
		while (argv[++i])
		{
			tab = ft_split(argv[i], '=');
			if ((tab_len(tab) == 1) && isallalphanum(argv[i]))
				unset_env(tab[0]);
			else
			{
				ft_printf(
			"minishell: unset: `%s': not a valid identifier\n", argv[i]);
				flag = 1;
			}
			free_s_tab(tab);
		}
	}
	return (flag);
}

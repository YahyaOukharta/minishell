/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:40 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/27 15:52:42 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*ft_key(char *s)
{
	int		i;
	char	*key;
	int		j;

	i = 0;
	j = -1;
	key = NULL;
	if (s)
	{
		while (s[i] != '\0' && s[i] != '=')
			i++;
		if (!(key = (char *)malloc(sizeof(char ) * (i + 1))))
			return (NULL);
		while (++j < i)
			key[j] = s[j];
		key[j] = '\0';
	}
	return (key);
}

char	*ft_value(char *s)
{
	char	*value;

	value = NULL;
	if (s)
	{
		if (!(value = ft_strdup(ft_strchr(s, '=') + 1)))
			return (NULL);
	}
	return (value);
}

void	init_environment(char **envp)
{
	int		i;
	t_env	*new;
	char	*n;

	i = 0;
	n = NULL;
	while (envp[i] != NULL)
	{
		n = ft_key(envp[i]);
		if (!string_equal(n, "OLDPWD"))
		{
			new = new_env(ft_key(envp[i]), ft_value(envp[i]));
			new->next = g_env;
			g_env = new;
		}
		free(n);
		i++;
	}
}

int		set_env(char *key, char *value)
{
	t_env *tmp;

	if (!key || !value)
		return (0);
	if (!g_env)
		return (0);
	else
	{
		tmp = g_env;
		while (tmp->next && !string_equal(tmp->key, key))
			tmp = tmp->next;
		if (!tmp->next && !string_equal(tmp->key, key))
			tmp->next = new_env(ft_strdup(key), ft_strdup(value));
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
		}
	}
	return (0);
}

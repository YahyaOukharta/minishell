/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:40 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/27 15:52:42 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset_env(char *key)
{
	t_env *tmp;
	t_env *trash;

	tmp = g_env;
	if (!g_env)
		return ;
	trash = NULL;
	if (string_equal(tmp->key, key))
	{
		trash = tmp;
		g_env = tmp->next;
	}
	else
	{
		while (tmp->next)
		{
			if (string_equal(tmp->next->key, key))
			{
				trash = tmp->next;
				tmp->next = trash->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (trash)
		free_one_env(trash);
}

t_env		*env_with_key(char *key)
{
	t_env *tmp;

	if (!g_env)
		return (0);
	tmp = g_env;
	while (tmp)
	{
		if (string_equal(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

int			get_env_len(void)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = g_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char		**get_env_tab(void)
{
	char	**tab;
	t_env	*tmp;
	int		i;

	if (!g_env)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (get_env_len() + 1))))
		return (0);
	i = 0;
	tmp = g_env;
	while (tmp)
	{
		tab[i] = ft_strjoin_va(3, tmp->key, "=", tmp->value);
		i++;
		tmp = tmp->next;
	}
	tab[i] = 0;
	return (tab);
}

void		free_env(void)
{
	while (g_env != NULL)
	{
		free(g_env->key);
		free(g_env->value);
		g_env = g_env->next;
	}
}

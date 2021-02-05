/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:40 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:52:42 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*get_env_to_delete(char *key)
{
	t_env	*tmp;
	t_env	*trash;

	tmp = g_env;
	while (tmp->next)
	{
		if (string_equal(tmp->next->key, key))
		{
			trash = tmp->next;
			tmp->next = trash->next;
			return (trash);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		free_one_env(t_env *e)
{
	if (e)
	{
		free(e->key);
		free(e->value);
		free(e);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:49 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:53:58 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tab_len(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

int		exists_in_tab(char *s, char **tab)
{
	while (*tab)
	{
		if (!ft_strncmp(s, *tab, MAX(ft_strlen(s), ft_strlen(*tab))))
			return (1);
		tab++;
	}
	return (0);
}

int		index_of_in_tab(char *s, char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(s, tab[i], MAX(ft_strlen(s), ft_strlen(tab[i]))))
			return (i);
		i++;
	}
	return (-1);
}

int		free_s_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
				free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:05:29 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/20 17:08:32 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_words(const char *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static int	get_word_len(const char *str, unsigned int index, char delim)
{
	int len;
	int i;

	len = 0;
	i = index;
	while (str[i] && str[i] != delim)
	{
		i++;
		len++;
	}
	return (len);
}

char		**free_tab(char **tab, size_t filled_elems)
{
	size_t i;

	i = 0;
	while (i < filled_elems)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

char		**ft_split(const char *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (str)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * (n_words(str, c) + 1))))
			return (0);
		i = 0;
		j = 0;
		while (i < n_words(str, c))
		{
			while (str[j] == c)
				j++;
			if (!(tab[i] = ft_substr(str, j, get_word_len(str, j, c))))
				return (free_tab(tab, i - 1));
			j += get_word_len(str, j, c);
			i++;
		}
		tab[i] = 0;
		return (tab);
	}
	return (0);
}

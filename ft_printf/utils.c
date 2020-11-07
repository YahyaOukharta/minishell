/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:26:10 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/08 11:52:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		index_of(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		len_without(char *str, char f)
{
	int		i;
	char	*p;

	i = 0;
	p = str;
	while (p && *p)
	{
		if (*p != f)
			i++;
		p++;
	}
	return (i);
}

char	*take_out(char *flgs, char f)
{
	int		i;
	int		j;
	char	*p;

	i = len_without(flgs, f);
	if (i == (int)ft_strlen(flgs))
		return (flgs);
	p = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	j = 0;
	while (flgs[j])
	{
		if (flgs[j] != f)
		{
			p[i] = flgs[j];
			i++;
		}
		j++;
	}
	p[i] = '\0';
	free(flgs);
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:20:47 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/20 16:32:27 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*append_n(char *s, char *line, int *i, int n)
{
	char	*t;

	t = NULL;
	while (n--)
	{
		t = append(s, line[*i]);
		*i += 1;
		t = append(s, line[*i]);
		*i += 1;
	}
	return (t);
}

int			escape(char *s, int pos)
{
	int i;
	int c;

	c = 0;
	i = 0;
	while (pos >= i)
	{
		if (s[pos] == '\\')
			c++;
		else
			break ;
		pos--;
	}
	if (c % 2 != 0)
		return (1);
	return (0);
}

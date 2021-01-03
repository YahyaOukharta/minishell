/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_nu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:23:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/30 15:18:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_insidethequote(char *s, int *i, char *m, char quote)
{
	char	*t;
	char	*str;

	t = NULL;
	str = NULL;
	if (s[*i] != quote && (s[*i] == '\'' || s[*i] == '\"'))
	{
		t = get_inside(s + *i, i, s[*i]);
		str = ft_strdup(m);
		if (m)
			free(m);
		m = ft_strjoin(str, t);
		if (t)
			free(t);
		if (str)
			free(str);
	}
	return (m);
}

char		*ft_new_inside(char *s, int *start, char quote)
{
	int		i;
	char	*rt;
	int		in;
	char	*c;
	char	*tmp;

	in = 1;
	i = 0;
	rt = NULL;
	c = NULL;
	tmp = NULL;
	while (i < (int)ft_strlen(s))
	{
		while (s[i] == quote)
		{
			i++;
			in++;
		}
		if (s[i] == '\\')
			i++;
		if ((s[i] == ' ' || s[i] == '>' || s[i] == '<' ||
		s[i] == '|' || s[i] == ';') && in % 2 == 0)
			break ;
		if ((in % 2 == 0) && s[i] != quote && i  > 0 && s[i -1]  != '\\' && QUOTE(s[i]) )
		{
			c = ft_new_inside(s + i+ 1, &i, s[i]);
			tmp = ft_strdup(rt);
			if (rt)
				free(rt);
			rt = ft_strjoin(tmp, c);
			if (c)
				free(c);
			if (tmp)
				free(tmp);
		}
		if (s[i] != quote)
			rt = append(rt, s[i]);
		i++;
	}
	*start += i;
	return (rt);
}

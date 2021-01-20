/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_nu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:23:07 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/19 18:55:43 by malaoui          ###   ########.fr       */
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
	rt = ft_strdup("");
	c = NULL;
	tmp = NULL;
	while (i < (int)ft_strlen(s))
	{
		if ((s[i] == '\\' && s[i + 1] == '\\' && quote == '\"') ||
		(s[i] == '\\' && s[i + 1] == '\"' && quote == '\"'))
		{
			i++;
			rt = append(rt, s[i++]);
			continue ;
		}
		while ((s[i] == quote && !escape(s, i - 1) && quote == '\"')
		|| ((s[i] == quote && quote == '\'')))
		{
			i++;
			in++;
		}
		if (s[i] == '\\' && s[i + 1] == quote && quote == '\'' && (in % 2) == 0)
		{
			i++;
			rt = append(rt, s[i++]);
			continue ;
		}
		if (s[i] == '\\' && (in % 2 == 0))
		{
			i++;
			rt = append(rt, s[i++]);
			continue ;
		}
		if ((s[i] == ' ' || s[i] == '>' || s[i] == '<' ||
		s[i] == '|' || s[i] == ';') && in % 2 == 0)
			break ;
		if ((in % 2 == 0) && s[i] != quote && QUOTE(s[i]) && !escape(s, i - 1))
		{
			c = ft_new_inside(s + i + 1, &i, s[i]);
			tmp = ft_strdup(rt);
			if (rt)
				free(rt);
			rt = ft_strjoin(tmp, c);
			if (c)
				free(c);
			if (tmp)
				free(tmp);
			i++;
			continue ;
		}
		if ((s[i] == ' ' || s[i] == '>' || s[i] == '<' ||
		s[i] == '|' || s[i] == ';') && in % 2 == 0)
			break ;
		if (s[i] != quote)
			rt = append(rt, s[i++]);
	}
	*start += i;
	return (rt);
}

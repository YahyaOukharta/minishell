/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_nu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:23:07 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/21 10:12:59 by malaoui          ###   ########.fr       */
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

int			check_escape_quote(char *s, t_var *u, char **rt)
{
	if ((s[u->i] == '\\' && s[u->i + 1] == '\\' && u->quote == '\"') ||
	(s[u->i] == '\\' && s[u->i + 1] == '\"' && u->quote == '\"'))
	{
		u->i++;
		*rt = append(*rt, s[u->i++]);
		return (1);
	}
	while ((s[u->i] == u->quote && !escape(s, u->i - 1) && u->quote == '\"')
	|| ((s[u->i] == u->quote && u->quote == '\'')))
	{
		u->i++;
		u->in++;
	}
	if ((s[u->i] == '\\' && s[u->i + 1] == u->quote
	&& u->quote == '\'' && (u->in % 2) == 0)
	|| (s[u->i] == '\\' && (u->in % 2 == 0)))
	{
		u->i++;
		*rt = append(*rt, s[u->i++]);
		return (1);
	}
	return (0);
}

int			recur_new_inside(t_var *u, char *s, char **rt)
{
	char	*c;
	char	*tmp;

	c = NULL;
	tmp = NULL;
	if ((u->in % 2 == 0) && s[u->i] != u->quote &&
	is_q(s[u->i]) && !escape(s, u->i - 1))
	{
		c = ft_new_inside(s + u->i + 1, &u->i, s[u->i]);
		tmp = ft_strdup(*rt);
		if (*rt)
			free(*rt);
		*rt = ft_strjoin(tmp, c);
		if (c)
			free(c);
		if (tmp)
			free(tmp);
		u->i++;
		return (1);
	}
	return (0);
}

char		*ft_new_inside(char *s, int *start, char quote)
{
	char	*rt;
	t_var	u;

	u.in = 1;
	u.i = 0;
	rt = ft_strdup("");
	u.quote = quote;
	while (u.i < (int)ft_strlen(s))
	{
		if (check_escape_quote(s, &u, &rt) == 1)
			continue ;
		if ((s[u.i] == ' ' || s[u.i] == '>' || s[u.i] == '<' ||
		s[u.i] == '|' || s[u.i] == ';') && u.in % 2 == 0)
			break ;
		if (recur_new_inside(&u, s, &rt) == 1)
			continue ;
		if ((s[u.i] == ' ' || s[u.i] == '>' || s[u.i] == '<' ||
		s[u.i] == '|' || s[u.i] == ';') && u.in % 2 == 0)
			break ;
		if (s[u.i] != u.quote)
			rt = append(rt, s[u.i++]);
	}
	*start += u.i;
	return (rt);
}

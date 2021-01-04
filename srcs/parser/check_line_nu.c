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

char		*new_inside_helper(char *s, int *i, char *rt)
{
	char *tmp;
	char *c;

	c = ft_new_inside(s + *i + 1, i, s[*i]);
	tmp = rt;
	rt = ft_strjoin(tmp, c);
	if (c)
		free(c);
	if (tmp)
		free(tmp);
	return (rt);
}

char		*ft_new_inside(char *s, int *start, char quote)
{
	int		i;
	char	*rt;
	int		in;

	in = 1;
	i = 0;
	rt = NULL;
	while (i < (int)ft_strlen(s))
	{
		while (i > 0 && s[i - 1] != '\\' && s[i] == quote)
		{
			i++;
			in++;
		}
		i += (s[i] == '\\' && QUOTE(s[i + 1]) ? 1 : 0);
		if (ft_strchr(" ><|;", s[i]) && !(in % 2))
			break ;
		if (!(in % 2) && s[i] != quote && i && s[i - 1] != '\\' && QUOTE(s[i]))
			rt = new_inside_helper(s, &i, rt);
		rt = (s[i] != quote || (s[i] == quote && s[i - 1] == '\\')
			? append(rt, s[i]) : rt);
		i++;
	}
	*start += i;
	return (rt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:23 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/12 16:36:45 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**realloc__(char **s, char *t)
{
	int		i;
	char	**r;

	i = -1;
	if (!(r = (char **)malloc(sizeof(char *) * (tab_len(s) + 2))))
		return (NULL);
	while (++i < tab_len(s))
	{
		r[i] = ft_strdup(s[i]);
		if (s[i])
			free(s[i]);
	}
	if (s)
		free(s);
	r[i] = ft_strdup(t);
	if (t)
		free(t);
	r[i + 1] = NULL;
	return (r);
}

void		rarg_norm(char *line, int *i, int *end, int *in)
{
	char	*tmp;

	tmp = NULL;
	*end = *i + 1;
	if ((tmp = ft_new_inside(line + *i + 1, end, line[*i])))
		*in = 1;
	if (tmp)
		free(tmp);
}

char		*rarg_fill_norm(char *s, char *line, int *i)
{
	char	*tmp;
	char	*h;

	tmp = ft_strdup(s);
	if (s)
		free(s);
	h = outside_quotes(line + *i, i);
	s = ft_strjoin(tmp, h);
	if (h)
		free(h);
	if (tmp)
		free(tmp);
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:29:27 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/21 10:12:59 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			fill_arg(char *line, t_arg *n, char **s)
{
	if (is_q(line[n->i]) && (n->in == 0))
		rarg_norm(line, &n->i, &n->end, &n->in);
	if ((n->i == n->end + 1) && n->in == 1)
	{
		n->in = 0;
		if (!ft_isalnum(line[n->i + 1]))
			return (1);
	}
	if (ft_isalnum(line[n->i]) && (n->in == 0))
	{
		*s = rarg_fill_norm(*s, line, &n->i);
		return (1);
	}
	return (0);
}

char		*get_rarg(char *line, int *pos)
{
	t_arg	n;
	char	*s;

	s = NULL;
	n.i = 0;
	n.in = 0;
	n.end = 0;
	while (line[n.i] != '\0')
	{
		if (fill_arg(line, &n, &s) == 1)
			break ;
		if (n.in == 0 && n.i > 0 &&
		((line[n.i] == '>' && (line[n.i + 1] != '>' && line[n.i - 1] != '>'))
			|| line[n.i] == '<'))
			break ;
		s = append(s, line[n.i++]);
	}
	*pos += n.i;
	return (s);
}

t_redir		get_tokens(char *s)
{
	int			i;
	int			end;
	int			in;
	t_redir		redir;

	i = 0;
	end = 0;
	in = 0;
	init_redir(&redir);
	while ((size_t)i < ft_strlen(s) && s[i] != '\0')
	{
		if (is_q(s[i]) && (end = quote_ends(s + i + 1, s[i])))
			quote_token(s, &i, &redir);
		else if ((s[i] == '>' && s[i + 1] == '>') ||
			s[i] == '>' || s[i] == '<')
			fill_redir(&redir, s, &i, in);
		else if (s[i] != ' ')
			redir.tokens = realloc__(redir.tokens, outside_quotes(s + i, &i));
		inc_(&i, s);
	}
	return (redir);
}

int			have_end(char *s, char quote, int *start)
{
	if (!s)
		return (0);
	while (*start < (int)ft_strlen(s))
	{
		if (s[*start] == quote && (!escape(s, *start - 1) && quote == '\"'))
		{
			*start += 1;
			return (1);
		}
		else if (s[*start] == quote && quote != '\"')
		{
			*start += 1;
			return (1);
		}
		*start += 1;
	}
	return (0);
}

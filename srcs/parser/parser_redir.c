/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:23 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/27 15:53:26 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**realloc__(char **s, char *t)
{
	int		i;
	char	**r;
	int		len;

	i = 0;
	len = tab_len(s);
	if (!(r = (char **)malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	while (i < len)
	{
		r[i] = ft_strdup(s[i]);
		if (s[i])
			free(s[i]);
		i++;
	}
	if (s)
		free(s);
	r[i] = ft_strdup(t);
	if (t)
		free(t);
	r[i + 1] = NULL;
	return (r);
}

char		*get_rarg(char *line, int *pos)
{
	int		i;
	int		end;
	int		in;
	char	*s;
	char	*tmp;
	char	*h;

	s = NULL;
	i = 0;
	in = 0;
	end = 0;
	tmp = NULL;
	h = NULL;
	while (line[i] != '\0')
	{
		if (in == 0 && QUOTE(line[i]))
		{
			end = i + 1;
			if ((tmp = inside_quotes(line + i + 1, &end, line[i])))
				in = 1;
			if (tmp)
				free(tmp);
		}
		if (i == end + 1 && in == 1)
		{
			in = 0;
			if (!ft_isalnum(s[i + 1]))
				break ;
		}
		if (ft_isalnum(line[i]) && in == 0)
		{
			tmp = ft_strdup(s);
			if (s)
				free(s);
			h = outside_quotes(line + i, &i);
			s = ft_strjoin(tmp, h);
			if (h)
				free(h);
			if (tmp)
				free(tmp);
			break ;
		}
		if (((line[i] == '>' && (line[i + 1] != '>' && line[i - 1] != '>'))
			|| line[i] == '<') && in == 0 && i > 0)
			break ;
		tmp = ft_strdup(s);
		if (s)
			free(s);
		s = append(tmp, line[i]);
		i++;
	}
	*pos += i;
	return (s);
}

int			quote_ends(char *s, char c)
{
	int	i;

	i = 0;
	if (QUOTE(s[i]) && i == 0)
		return (1);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

void		fill_redir(t_redir *redir, char *s, int *i)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
		redir->outs = realloc__(redir->outs, get_rarg(s + *i, i));
	else if (s[*i] == '>')
		redir->outs = realloc__(redir->outs, get_rarg(s + *i, i));
	else
		redir->ins = realloc__(redir->ins, get_rarg(s + *i, i));
}

t_redir		get_tokens(char *s)
{
	int			i;
	int			end;
	int			in;
	t_redir		redir;
	char		*tmp;

	i = 0;
	end = 0;
	in = 0;
	redir.ins = NULL;
	redir.outs = NULL;
	redir.tokens = NULL;
	tmp = NULL;
	while (s[i] != '\0')
	{
		if (QUOTE(s[i]) && (end = quote_ends(s + i + 1, s[i])))
		{
			i++;
			redir.tokens = realloc__(redir.tokens,
				inside_quotes(s + i, &i, s[i - 1]));
			if (QUOTE(s[i]))
				i++;
		}
		else if ((s[i] == '>' && s[i + 1] == '>') ||
			s[i] == '>' || s[i] == '<')
		{
			if (in == 0 && ((s[i] == '>' && s[i + 1] == '>') ||
			s[i] == '>' || s[i] == '<'))
				fill_redir(&redir, s, &i);
			if ((s[i] == ' ' || s[i + 1] == '\0') && s[i] != '>' && s[i] != '<')
				i++;
		}
		else if (s[i] != ' ')
			redir.tokens = realloc__(redir.tokens, outside_quotes(s + i, &i));
		if (s[i] != '\0' && (s[i] == ' ' || s[i + 1] == '\0')
			&& s[i] != '>' && s[i] != '<')
			i++;
	}
	return (redir);
}

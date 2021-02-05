/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:20 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/21 10:12:59 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_quotes(char *s, int *pos)
{
	int		start;
	int		end;
	char	quote;

	start = 0;
	end = ft_strlen(s);
	quote = '0';
	while (start < end)
	{
		if ((s[start] == '\'' || s[start] == '\"') && !escape(s, start - 1))
		{
			*pos = start;
			quote = s[start++];
			if (have_end(s, quote, &start) == 0)
				return (0);
			start--;
		}
		start++;
	}
	return (1);
}

int			has_alnum(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		if (ft_isalnum(s[i++]) || is_q(s[i]))
			return (1);
	return (0);
}

int			check_pipe(char *s)
{
	char	**split;
	int		v;
	int		rt;
	int		i;
	char	*t;

	i = -1;
	rt = 0;
	split = parser_split(s, '|');
	v = 0;
	while (split[++i] != NULL)
	{
		if (ft_strlen((t = ft_strtrim(split[i], " \t"))) > 0
			&& has_alnum(split[i]))
			v++;
		free(t);
		free(split[i]);
	}
	free(split);
	if (v == cparser(s, '|'))
		rt = 1;
	return (rt);
}

int			has_redir(char *s, int *pos)
{
	int		i;
	int		in;
	int		end;

	i = 0;
	in = 0;
	end = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			norm_quote(s, &i, &in, &end);
			if (i + 1 == end)
				in = 0;
			if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>",
				ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
			{
				*pos += i;
				return (1);
			}
			i++;
		}
		return (0);
	}
	return (0);
}

int			check_pipeline(char *s)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (s)
	{
		while (s[i] != '\0' && s[i] != ';')
		{
			if (ft_isalnum(s[i]))
				flag = 1;
			i++;
		}
		if (!flag && s[i] == ';')
			return (0);
		while (s[i] != '\0')
		{
			if (s[i] == ';' && i == 0 && !escape(s, i - 1))
				return (0);
			if (s[i] == ';' && (no_alpha(s + i + 1) == 1) && !escape(s, i - 1))
				return (0);
			i++;
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:20 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/28 17:09:17 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			have_end(char *s, char quote, int *start)
{
	while (*start < (int)ft_strlen(s))
	{
		if (s[*start] == quote)
		{
			*start += 1;
			return (1);
		}
		*start += 1;
	}
	return (0);
}

int			check_quotes(char *s, int *pos)
{
	int		i;
	int		start;
	int		end;
	char	quote;

	i = 0;
	start = 0;
	end = ft_strlen(s);
	quote = '0';
	while (start < end)
	{
		if (s[start] == '\'' || s[start] == '\"')
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

int			check_pipe(char *s)
{
	char	**split;
	int		v;
	int		rt;
	int		i;

	i = -1;
	rt = 0;
	split = parser_split(s, '|');
	v = 0;
	while (split[++i] != NULL)
	{
		if (ft_strlen(split[i]) > 0)
			v++;
		free(split[i]);
	}
	free(split);
	if ((v - 1) == cparser(s, '|'))
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
			if (i == end)
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
	return (1);
}

int			check_pipeline(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] == ';' && i == 0)
				return (0);
			if (s[i] == ';' && no_alpha(s + i + 1) == 1)
				return (0);
			i++;
		}
	}
	return (1);
}

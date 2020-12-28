/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:20 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/28 12:19:54 by malaoui          ###   ########.fr       */
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

int			check_arg(char *s)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	if (s)
	{
		while (!(s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>",
			ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
			i++;
		if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>",
			ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
		{
			if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<')
				i += 1;
			else
				i++;
		}
		while (s[i] != '\0')
		{
			if (ft_isalnum(s[i]) || QUOTE(s[i]))
				return (0);
			if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>",
				ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0)
				return (1);
			if (s[i] != '\0')
				i++;
		}
	}
	return (1);
}

int			ft_strsearch(char *s, char n)
{
	int		i;
	int		in;
	int		end;
	char	*tmp;

	i = 0;
	in = 0;
	end = 0;
	tmp = NULL;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (QUOTE(s[i]) && in == 0)
			{
				end = i + 1;
				if ((tmp = inside_quotes(s + i + 1, &end, s[i])))
					in = 1;
				if (tmp)
					free(tmp);
			}
			if (i == end)
				in = 0;
			if (s[i] == n && in == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int			has_redir(char *s, int *pos)
{
	int		i;
	int		in;
	int		end;
	char	*tmp;

	tmp = NULL;
	if (s)
	{
		i = 0;
		in = 0;
		end = 0;
		while (s[i] != '\0')
		{
			if (QUOTE(s[i]) && in == 0)
			{
				end = i + 1;
				if ((tmp = inside_quotes(s + i + 1, &end, s[i])))
					in = 1;
				if (tmp)
					free(tmp);
			}
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
	}
	else
		return (1);
	return (0);
}

int			check_redir(char *s)
{
	int i;

	i = 0;
	while (has_redir(s + i, &i) == 1 && s[i] != '\0')
	{
		if (ft_strsearch(s + i, '>') && !ft_strnstr(s, ">>", ft_strlen(s)))
			if (check_arg(s + i))
				return (0);
		if (ft_strsearch(s + i, '<') && !ft_strnstr(s + i, "<<", ft_strlen(s)))
			if (check_arg(s + i))
				return (0);
		if (ft_strnstr(s + i, ">>", ft_strlen(s + i)) != NULL)
			if (check_arg(s + i))
				return (0);
		if (s[i] != '\0')
			i++;
	}
	return (1);
}

int			check_pipeline(char *s)
{
	int i;

	i = 0;
	if (s)
		if (s[0] == ';')
			return (0);
	return (1);
}

int			check_syntax(char *s)
{
	int		pos;
	char	*e;

	pos = 0;
	if (ft_strsearch(s, ';'))
	{
		if (check_pipeline(s) == 0)
		{
			ft_printf("Syntax Error Near %s\n", s + pos);
			return (0);
		}
	}
	if (ft_strchr(s, '\"') || ft_strchr(s, '\''))
	{
		if (check_quotes(s, &pos) == 0)
		{
			ft_printf("Syntax Error Near %s\n", s + pos);
			return (0);
		}
	}
	if (ft_strsearch(s, '|'))
	{
		if (check_pipe(s) == 0)
		{
			ft_printf("Syntax Error Near %s\n", ft_strchr(s, '|'));
			return (0);
		}
	}
	if (ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strnstr(s, ">>",
		(ft_strlen(s) < 3 ? 3: ft_strlen(s))))
	{
		if (check_redir(s) == 0)
		{
			e = (ft_strchr(s, '>') == NULL ? (ft_strchr(s, '<') == NULL ?
				ft_strnstr(s, ">>", (ft_strlen(s) < 3 ? 3 :
				ft_strlen(s))) : ft_strchr(s, '<')) : ft_strchr(s, '>'));
			ft_printf("Syntax Error Near %s\n", e);
			return (0);
		}
	}
	return (1);
}

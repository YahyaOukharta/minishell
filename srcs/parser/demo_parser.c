/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:34 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/06 10:02:04 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_escape(char *s, int pos)
{
	int i;
	int c;

	c = 0;
	i = 0;
	while (pos >= i)
	{
		if (s[pos] == '\\')
			c++;
		else
			break ;
		pos--;
	}
	if (c % 2 != 0)
		return (1);
	return (0);
}

int		cparser(char *s, char q)
{
	int		i;
	int		in;
	int		c;
	int		end;

	i = 0;
	in = 0;
	c = 0;
	end = 0;
	while (s[i] != '\0')
	{
		if (QUOTE(s[i]) && !_escape(s, i - 1) && in == 0)
		{
			end = i + 1;
			if (have_end(s + i + 1, s[i], &end))
				in = 1;
		}
		if (i == end)
			in = 0;
		if (in == 0 && s[i] == q && !_escape(s, i - 1))
			c++;
		i++;
	}
	return (c);
}

char	*append(char *s, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (!(str = malloc(sizeof(char ) * (len + 2))))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	if (s)
		free(s);
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

void	get_arg_helper(char *line, int *end, int *in, char **tmp)
{
	if ((*tmp = ft_new_inside(line + 1, end, *line)))
	{
		*in = 1;
		free(*tmp);
	}
}

char	*get_arg(char *line, char c, int *pos)
{
	int		i;
	int		end;
	int		in;
	char	*tmp[2];

	i = 0;
	in = 0;
	ft_bzero(tmp, 2 * sizeof(char *));
	while (line[i])
	{
		if (in == 0 && QUOTE(line[i]) && !_escape(line, i - 1))
		{
			end = i + 1;
			get_arg_helper(&line[i], &end, &in, &tmp[1]);
			in = 1;
		}
		(i + 1 == end) ? (in = 0) : 0;
		if (line[i] == c && in == 0 && !_escape(line, i - 1))
		{
			*pos += i;
			break ;
		}
		tmp[0] = append(tmp[0], line[i++]);
	}
	*pos += (line[i] == '\0' ? i - 1 : 0);
	return (tmp[0]);
}

char	**parser_split(char *line, char c)
{
	int		i;
	int		nb_c;
	char	**split;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	nb_c = cparser(line, c) + 1;
	if (!(split = (char **)malloc(sizeof(char *) * (nb_c + 1))))
		return (NULL);
	i = 0;
	while (i < nb_c)
	{
		tmp = get_arg(line + j, c, &j);
		split[i] = ft_strtrim(tmp, " \t");
		free(tmp);
		j++;
		i++;
	}
	split[i] = NULL;
	return (split);
}

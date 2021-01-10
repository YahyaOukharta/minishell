/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:39:29 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/10 18:01:03 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_inc_arg(char *s, int *i, int *in)
{
	while (!(s[*i] == '>' || s[*i] == '<' || ft_strncmp(s, ">>",
	ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && *in == 0)
		*i += 1;
	if ((s[*i] == '>' || s[*i] == '<' || ft_strncmp(s, ">>",
	ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && *in == 0)
	{
		if (s[*i] == '>' && s[*i + 1] == '>')
			*i += 2;
		else if (s[*i] == '<')
			*i += 1;
		else
			*i += 1;
	}
}

int			check_arg(char *s)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	if (s)
	{
		check_inc_arg(s, &i, &in);
		while (s[i] != '\0')
		{
			if (ft_isalnum(s[i]) || (QUOTE(s[i]) && !_escape(s, i - 1)))
				return (0);
			if ((s[i] == '>' || s[i] == '<' || ft_strncmp(s, ">>",
				ft_strlen(s) < 3 ? 3 : ft_strlen(s)) == 0) && in == 0 && !_escape(s, i - 1))
				return (1);
			if (s[i] != '\0')
				i++;
		}
	}
	return (1);
}

void		norm_quote(char *s, int *i, int *in, int *end)
{
	char *tmp;

	tmp = NULL;
	if (*in == 0 && QUOTE(s[*i]))
	{
		*end = *i + 1;
		if ((tmp = ft_new_inside(s + *i + 1, end, s[*i])))
			*in = 1;
		if (tmp)
			free(tmp);
		//in = 1;
	}
}

int			ft_strsearch(char *s, char n)
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
			//in == 0 ? norm_quote(s, &i, &in, &end) : 0;
			if (in == 0)
				norm_quote(s, &i, &in, &end);
			if (i == end)
				in = 0;
			if (s[i] == n && in == 0 && !_escape(s, i - 1))
				return (1);
			i++;
		}
	}
	return (0);
}

int			check_redir(char *s)
{
	int i;

	i = 0;
	while (has_redir(s + i, &i) == 1 && s[i] != '\0')
	{
		if (ft_strsearch(s + i, '>') && !ft_strnstr(s + i, ">>", ft_strlen(s)) && !_escape(s, i - 1))
			if (check_arg(s + i))
				return (0);
		if (ft_strsearch(s + i, '<') && !ft_strnstr(s + i, "<<", ft_strlen(s)) && !_escape(s, i - 1))
			if (check_arg(s + i))
				return (0);
		if (ft_strnstr(s + i, ">>", ft_strlen(s + i)) != NULL && !_escape(s, i - 1))
			if (check_arg(s + i))
				return (0);
		if (s[i] != '\0')
			i++;
	}
	return (1);
}

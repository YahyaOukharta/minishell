/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:57:12 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/28 12:15:39 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_inside(char *s, int *start, char quote)
{
	char 	*t;
	int i;

	i = 1;
	t = ft_strdup("");
	while (s[i] != '\0' && s[i] != quote)
		t = append(t, s[i++]);
	if (s[i] == '\0')
		i--;
	if (s[i] == quote)
		i++;
	*start += i;
	return (t);
}

char		*inside_quotes(char *s, int *start, char quote)
{
	int		i;
	char	*m;
	char	*t;
	char	*str;


	i = 0;
	m = NULL;
	t = NULL;
	str = NULL;
	while (s[i] != '\0')
	{
		if (QUOTE(s[i]) && s[i] != quote)
		{
			t = get_inside(s + i, &i, s[i]);
			str = ft_strdup(m);
			if (m)
			 free(m);
			m = ft_strjoin(str, t); 
			if (t)
			 free(t);
			if (str)
				free(str);
		}
		// if (s[i] == quote && !(ft_isalnum(s[i + 1])))
		// {
		// 	*start += i;
		// 	break ;
		// }
		//else
		if (s[i] == quote && ft_isalnum(s[i + 1]))
		{
			m = get_norm_outside(&i, m, s, start);
			break ;
		}
		if (s[i] != quote)
			m = append(m, s[i]);
		if (s[i] != '\0')
			i++;
	}
	// if (s[i] == '\0')
	// 	i--;
	*start += i;
	if (m == NULL)
		m = ft_strdup("");
	return (m);
}

t_exp		inp(char *s)
{
	int		i;
	t_exp	in;
	int		end;

	i = 0;
	end = 0;
	in.sgl = 0;
	in.dbl = 0;
	while (s[i] != '\0')
	{
		if (QUOTE(s[i]))
		{
			if (have_end(s + i + 1, s[i], &end) && s[i] == '\'')
				in.sgl += 1;
			if (have_end(s + i + 1, s[i], &end) && s[i] == '\"')
				in.dbl += 1;
		}
		if (s[i] == '$')
			return (in);
		i++;
	}
	return (in);
}

char		*env_normed(char *s, char *line, int *i)
{
	char	*tmp;
	char	*t;

	t = NULL;
	tmp = ft_strdup(s);
	if (s)
		free(s);
	t = handle_env(line + *i, i);
	s = ft_strjoin(tmp, t);
	free(tmp);
	if (t)
		free(t);
	return (s);
}

char		*ft_env(char *line)
{
	int		i;
	char	*s;
	t_exp	in;

	i = 0;
	s = NULL;
	in.sgl = 0;
	in.dbl = 0;
	while (line[i] != '\0')
	{
		if (QUOTE(line[i]))
		{
			in = inp(line + i);
			while (QUOTE(line[i]))
				s = append(s, line[i++]);
		}
		if (line[i] == '$' && (in.sgl > 1 || in.dbl > 0 || (in.sgl == in.dbl)))
			s = env_normed(s, line, &i);
		else if (line[i] != '\0')
			s = append(s, line[i++]);
	}
	return (s);
}

char		*check_line(char *line)
{
	char	*rt;

	rt = NULL;
	if (line == NULL)
		return (NULL);
	if (!(check_syntax(line)))
		return (NULL);
	if (ft_strchr(line, '$'))
	{
		rt = ft_env(line);
		if (line)
			free(line);
		line = ft_strdup(rt);
		if (rt)
			free(rt);
	}
	return (line);
}

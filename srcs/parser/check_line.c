/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:57:12 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/06 18:41:42 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_inside(char *s, int *start, char quote)
{
	char	*t;
	int		i;

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
		while ((size_t)(i + 1) < ft_strlen(s) && QUOTE(s[i]))
		{
			end = i;
			if (have_end(s + i, s[i], &end) && s[i] == '\'')
				in.sgl += 1;
			if (have_end(s + i, s[i], &end) && s[i] == '\"')
				in.dbl += 1;
			i++;
		}
		if (s[i] == '$')
			return (in);
		if (s[i] != '\0')
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
		while ((QUOTE(line[i]) && i == 0)
			|| (i > 0 && line[i - 1] != '\\' && (QUOTE(line[i]))))
		{
			in.dbl += (line[i] == '\"' ? 1 : 0);
			in.sgl += (line[i] == '\'' ? 1 : 0);
			s = append(s, line[i++]);
		}
		i += (line[i] == '\\' && line[i + 1] == '$' && in.sgl == 0 ? 1 : 0);
		if (i > 1 && line[i - 1] != '\\' && line[i] == '$' && in.sgl % 2 != 1)
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
	/*if (ft_strchr(line, '$'))
	{
		rt = ft_env(line);
		if (line)
			free(line);
		line = ft_strdup(rt);
		if (rt)
			free(rt);
	}*/
	return (line);
}

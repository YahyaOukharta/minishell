/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 12:14:38 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/19 18:55:12 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_get_value(char *line, int *pos)
{
	int		i;
	char	*s;
	char	*key;
	t_env	*env;

	i = 0;
	s = NULL;
	key = NULL;
	while (line[i] != '\0' && (ft_isalnum(line[i])
	|| !ft_strchr(" =\\\"\'],$@;|><", line[i])))
		i++;
	key = ft_substr(line, 0, i);
	env = env_with_key(key);
	if (env != NULL)
		s = ft_strdup(env->value);
	else
		s = ft_strdup("");
	if (key)
		free(key);
	*pos += i;
	return (s);
}

char		*dollar_norm(char *s, int *i, int value)
{
	char	*tmp;
	char	*p;

	tmp = NULL;
	p = NULL;
	tmp = ft_strdup(s);
	if (s)
		free(s);
	p = ft_itoa(value);
	s = ft_strjoin(tmp, p);
	if (tmp)
		free(tmp);
	if (p)
		free(p);
	*i += 2;
	return (s);
}

char		*handle_escape(char *s)
{
	int		i;
	char	*r;
	int		len;

	i = 0;
	r = ft_strdup("");
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == '\\')
		{
			r = append(r, '\\');
			r = append(r, s[i++]);
		}
		else
			r = append(r, s[i++]);
	}
	return (r);
}

char		*dollar_norm_dollar(char *s, int *i, char *line)
{
	char	*tmp;
	char	*p;
	int		env;

	env = 0;
	p = NULL;
	tmp = NULL;
	*i += 1;
	if (s)
	{
		tmp = ft_strdup(s);
		free(s);
	}
	else
		tmp = ft_strdup("");
	if (ft_isalnum(line[*i]) || line[*i] == '_')
		env = 1;
	p = handle_escape(ft_get_value(line + *i, i));
	s = ft_strjoin(tmp, ((ft_strlen(p) == 0 && env == 0) ? "$" : p));
	if (tmp)
		free(tmp);
	if (p)
		free(p);
	return (s);
}

char		*handle_env(char *line, int *pos)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	while (line[i] == '$' && line[i + 1] == '$')
		s = dollar_norm(s, &i, g_child);
	if (line[i] == '$' && line[i + 1] == '?')
		s = dollar_norm(s, &i, g_status);
	else if (line[i] == '$' && (line[i + 1] == '_' ||
	!ft_strchr("0123456789-+=", line[i + 1])))
		s = dollar_norm_dollar(s, &i, line);
	else if (line[i] == '$' && !ft_strchr("0123456789", line[i + 1]))
		append_n(s, line, &i, 2);
	else
	{
		i += 2;
		s = line[i] == '\0' ? append(s, '\0') : s;
		while (i < (int)ft_strlen(line))
			s = append(s, line[i++]);
	}
	*pos += i;
	return (s);
}

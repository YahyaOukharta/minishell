/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:16 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/27 15:53:18 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*env_value(char *key)
{
	int		l;
	int		t;
	int		len;
	t_env	s;

	l = 0;
	t = ft_strlen(key);
	len = 0;
	s = *g_env;
	while (s.next != NULL)
	{
		l = ft_strlen(s.key);
		len = (l > t) ? l : t;
		if (ft_strncmp(s.key, key, len) == 0)
			return ((s.value));
		s = *(s.next);
	}
	return (NULL);
}

char		*get_key(char *s, int *pos)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	if (s[i] == '$')
		i++;
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]) == 0)
		{
			i--;
			break ;
		}
		i++;
	}
	key = ft_substr(s, 1, i);
	*pos += i;
	return (key);
}

int			ft_count_char(char *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
		if (s[i++] == c)
			n++;
	return (n);
}

t_env		*get_env(char *line, int *pos)
{
	int		i;
	char	*key;
	t_env	*s;

	i = 0;
	key = NULL;
	while (line[i] != '\0')
	{
		if (ft_isalpha(line[i]) == 0)
			break ;
		*pos += 1;
		i += 1;
	}
	if (line[i] == '\0')
		*pos -= 1;
	key = ft_substr(line, 0, i);
	s = env_with_key(key);
	free(key);
	return (s);
}

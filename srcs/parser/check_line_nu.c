/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_nu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:23:07 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/30 14:59:59 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_insidethequote(char *s, int *i, char *m, char quote)
{
	char	*t;
	char	*str;

	t = NULL;
	str = NULL;
	if (s[*i] != quote && (s[*i] == '\'' || s[*i] == '\"'))
	{
		t = get_inside(s + *i, i, s[*i]);
		str = ft_strdup(m);
		if (m)
			free(m);
		m = ft_strjoin(str, t);
		if (t)
			free(t);
		if (str)
			free(str);
	}
	return (m);
}

char		*inside_quotes(char *s, int *start, char quote)
{
	int		i;
	char	*m;

	i = 0;
	m = NULL;
	while (s[i] != '\0')
	{
		m = ft_insidethequote(s, &i, m, quote);
		if (s[i] == quote && s[i + 1] != ' ')
		{
			m = get_norm_outside(&i, m, s, start);
			break ;
		}
		else if (s[i] == quote && !ft_isalnum(s[i + 1]))
		{
			i++;
			break ;
		}
		if (s[i] != quote && s[i] != '\0')
			m = append(m, s[i++]);
	}
	*start += i;
	if (m == NULL)
		m = ft_strdup("");
	return (m);
}

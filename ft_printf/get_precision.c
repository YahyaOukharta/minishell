/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:05:39 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:05:54 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_specifiers.h"

char	*get_precision(char *conv, const char *t_convs)
{
	int		i;
	char	*res;
	char	*dot;
	char	*s;

	dot = ft_strrchr(conv, '.');
	if (!dot)
		return (0);
	i = 0;
	s = dot + 1;
	while (ft_isdigit(s[i]) || s[i] == '*')
		i++;
	if (i == 0)
		return (ft_strdup("0"));
	if (((res = ft_memchr(s, '*', i)) && i != 1)
		|| !ft_memchr(t_convs, s[i], ft_strlen(t_convs)))
		return (0);
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_memcpy(res, s, i);
	res[i] = '\0';
	return (res);
}

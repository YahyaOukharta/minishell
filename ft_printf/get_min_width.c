/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:06:22 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:06:25 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_specifiers.h"

char	*get_min_width(char *conv, const char *flags)
{
	char	*res;
	int		i;
	char	*flgs;
	char	*s;

	flgs = get_flags(conv, flags);
	if (flgs)
	{
		s = ft_strnstr(conv, flgs, ft_strlen(conv)) + ft_strlen(flgs);
		free(flgs);
	}
	else
		s = conv;
	i = 0;
	while (ft_isdigit(s[i]) || s[i] == '*')
		i++;
	if (i == 0 || ((res = ft_memchr(s, '*', i)) && i != 1))
		return (0);
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strlcpy(res, s, i + 1);
	return (res);
}

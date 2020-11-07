/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:05:02 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:05:29 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_specifiers.h"

char	*get_flags(char *conv, const char *flags)
{
	int		i;
	char	*s;
	char	*res;

	s = conv;
	i = 0;
	while (ft_memchr(flags, *s, ft_strlen(flags)))
	{
		s++;
		i++;
	}
	if (i > 0)
	{
		res = (char *)malloc(i + 1);
		ft_memcpy(res, conv, i);
		res[i] = '\0';
	}
	else
		res = 0;
	return (res);
}

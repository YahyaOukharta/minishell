/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:17:38 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:17:40 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_specifiers.h"

char	*get_conv(char *start, const char *t_convs)
{
	int		len;
	char	*p;
	char	*conv;

	p = start + 1;
	len = 0;
	while (*p && !(ft_memchr(t_convs, *p, ft_strlen(t_convs))))
	{
		len++;
		p++;
	}
	if (!ft_memchr(t_convs, *p, ft_strlen(t_convs)))
		return (0);
	else
	{
		len++;
		if (!(conv = (char *)malloc(len + 1)))
			return (0);
		ft_memcpy(conv, start + 1, len);
		conv[len] = '\0';
		return (conv);
	}
}

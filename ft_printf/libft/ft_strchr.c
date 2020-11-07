/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:32:00 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/12 00:00:23 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (*s == (char)c)
			return (s);
		s++;
		len--;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:48:54 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/11 23:52:16 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = ft_strlen(str);
	s += len;
	while (len >= 0)
	{
		if (*s == (char)c)
			return (s);
		s--;
		len--;
	}
	return (0);
}

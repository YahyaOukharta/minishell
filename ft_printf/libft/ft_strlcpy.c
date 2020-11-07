/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:01:55 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/12 13:14:52 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t bufsize)
{
	size_t			i;
	unsigned char	*s;

	if (dst && src)
	{
		s = (unsigned char *)src;
		i = 0;
		if (bufsize > 0)
		{
			while (s[i] && i < bufsize - 1)
			{
				*dst = s[i];
				i++;
				dst++;
			}
			*dst = '\0';
		}
		return (ft_strlen(src));
	}
	return (0);
}

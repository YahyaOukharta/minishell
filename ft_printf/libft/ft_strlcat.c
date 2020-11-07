/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:07:15 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/16 22:29:24 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t bufsize)
{
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	if (dstlen < bufsize)
	{
		ft_strlcpy(dst + dstlen, src, bufsize - dstlen);
		return (dstlen + ft_strlen(src));
	}
	return (ft_strlen(src) + bufsize);
}

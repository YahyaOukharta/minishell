/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:21:55 by youkhart          #+#    #+#             */
/*   Updated: 2020/02/19 21:13:52 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*sub;

	if (str)
	{
		if (ft_strlen(str) < start)
			len = 0;
		sub = (char *)malloc(len + 1);
		if (!sub)
			return (0);
		ft_strlcpy(sub, str + start, len + 1);
		return (sub);
	}
return (0);
}

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
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] == c)
				return ((char *)str + i);
			i++;
		}
		if (str[i] == c)
			return ((char *)str + i);
	}
	return (NULL);
}

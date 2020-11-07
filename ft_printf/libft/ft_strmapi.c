/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:40:10 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/20 17:11:37 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (str)
	{
		result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!result)
			return (0);
		i = 0;
		while (str[i])
		{
			result[i] = f(i, str[i]);
			i++;
		}
		result[i] = '\0';
		return (result);
	}
	return (0);
}

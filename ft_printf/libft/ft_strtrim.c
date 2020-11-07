/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:12:44 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/20 16:11:56 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trimmed_len(const char *src, const char *set)
{
	size_t len;
	size_t srclen;
	size_t i;

	i = 0;
	len = 0;
	srclen = ft_strlen(src);
	while (i < srclen && ft_strchr(set, src[i]))
	{
		i++;
		len++;
	}
	i = srclen - 1;
	while ((int)i > 0 && ft_strchr(set, src[i]))
	{
		i--;
		len++;
	}
	return (srclen - len);
}

char			*ft_strtrim(const char *str, const char *set)
{
	size_t	i;
	char	*result;
	size_t	final_len;

	if (str && set)
	{
		final_len = trimmed_len(str, set);
		final_len = ((int)final_len < 0 ? 0 : final_len);
		result = (char *)malloc(sizeof(char) * (final_len + 1));
		if (!result)
			return (0);
		i = 0;
		while (i < ft_strlen(str) && ft_strchr(set, str[i]))
			i++;
		ft_strlcpy(result, &str[i], final_len + 1);
		return (result);
	}
	return (0);
}

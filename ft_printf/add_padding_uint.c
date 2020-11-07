/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_uint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:53:30 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:42:09 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	*add_unsigned_padding(char *arg, size_t w, size_t v_len, char flag)
{
	char *res;

	if (!(res = (char *)malloc(sizeof(char) * (w + 1))))
		return (0);
	if (flag == '-')
	{
		ft_strlcpy(res, arg, w + 1);
		ft_memset(res + v_len, ' ', w - v_len);
	}
	else
	{
		ft_strlcpy(res + (w - v_len), arg, v_len + 1);
		ft_memset(res, (flag == '0' ? '0' : ' '), w - v_len);
	}
	res[w] = '\0';
	free(arg);
	return (res);
}

char	*add_padding_uint(char *arg, char *width, const char *flags)
{
	char	flag;
	size_t	w;
	size_t	v_len;

	if (!width)
		return (arg);
	flag = get_active_flag(flags);
	w = ft_atoi(width);
	v_len = ft_strlen(arg);
	if (!w && !ft_atoi(arg))
	{
		free(arg);
		return (ft_strdup(""));
	}
	if (w <= v_len)
		return (arg);
	return (add_unsigned_padding(arg, w, v_len, flag));
}

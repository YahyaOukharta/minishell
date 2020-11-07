/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:22:17 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:48:46 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

static char	*add_signed_padding(char *arg, size_t w, size_t v_len, char flag)
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
		if (flag == '0' && ft_atoi(arg) < 0)
			ft_swap(res, res + w - v_len);
	}
	res[w] = '\0';
	free(arg);
	return (res);
}

char		*add_padding_int(char *arg, char *width, const char *flags)
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
	return (add_signed_padding(arg, w, v_len, flag));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:20:44 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:43:23 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	*add_padding_char(char *arg, char *width, const char *flags)
{
	char	flag;
	char	*res;
	size_t	w;
	size_t	v_len;

	if (!width || ft_atoi(width) <= 1)
		return (arg);
	flag = get_active_flag(flags);
	v_len = (!*arg ? 0 : 1);
	w = (!*arg ? ft_atoi(width) - 1 : ft_atoi(width));
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
	free(arg);
	res[w] = '\0';
	return (res);
}

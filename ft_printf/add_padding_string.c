/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:59:29 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:38:17 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	*add_padding_string(char *arg, char *width, const char *flags)
{
	char	flag;
	char	*res;
	size_t	w;
	size_t	v_len;

	if (!width || ft_atoi(width) <= (int)ft_strlen(arg))
		return (arg);
	flag = get_active_flag(flags);
	w = ft_atoi(width);
	v_len = ft_strlen(arg);
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

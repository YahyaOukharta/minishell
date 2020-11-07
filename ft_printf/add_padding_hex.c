/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:32:54 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:33:34 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	*add_padding_hex(char *arg, char *width, const char *flags)
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

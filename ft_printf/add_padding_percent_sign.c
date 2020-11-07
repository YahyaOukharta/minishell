/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_percent_sign.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:41:17 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:41:47 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	*add_padding_percent_sign(char *arg, char *width, const char *flags)
{
	char	flag;
	size_t	w;
	size_t	v_len;

	if (!width || ft_atoi(width) <= (int)ft_strlen(arg))
		return (arg);
	flag = get_active_flag(flags);
	w = ft_atoi(width);
	v_len = 1;
	return (add_unsigned_padding(arg, w, v_len, flag));
}

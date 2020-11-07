/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_active_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:38:21 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:39:07 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

char	get_active_flag(const char *flags)
{
	char flag;
	char *p;

	p = (char *)flags;
	flag = 0;
	while (p && *p)
	{
		if (*p == '0')
			flag = '0';
		if (*p == '-')
		{
			flag = '-';
			break ;
		}
		p++;
	}
	return (flag);
}

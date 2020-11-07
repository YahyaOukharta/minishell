/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_va.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:23:27 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 16:23:28 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

char	*ft_strjoin_va(size_t n, ...)
{
	va_list		args;
	size_t		i;
	char		*res;
	char		*tmp;

	res = ft_strdup("");
	va_start(args, n);
	i = 0;
	while (i < n)
	{
		tmp = ft_strjoin(res, va_arg(args, char *));
		free(res);
		res = tmp;
		i++;
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:43:22 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/06 22:44:47 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char	*add_precision_s(char *arg, char *precision)
{
	size_t	p;
	size_t	v_len;
	char	*res;
	int		size;

	if (!precision)
		return (arg);
	p = ft_atoi(precision);
	if (!p)
	{
		free(arg);
		return (ft_strdup(""));
	}
	v_len = ft_strlen(arg);
	size = (p < v_len ? p : v_len);
	res = (char *)malloc(sizeof(char) * size + 1);
	ft_memcpy(res, arg, size);
	res[size] = '\0';
	free(arg);
	return (res);
}

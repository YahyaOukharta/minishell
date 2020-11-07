/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:42:41 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/06 22:43:07 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char	*add_precision_int(char *arg, char *precision)
{
	char	*s;

	if (!precision)
		return (arg);
	if (ft_atoi(arg) < 0)
		precision = ft_itoa(ft_atoi(precision) + 1);
	s = add_padding_int(arg, precision, "0");
	return (s);
}

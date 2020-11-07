/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision_uint.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:35:55 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/06 22:36:21 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char	*add_precision_uint(char *arg, char *precision)
{
	char	*s;

	if (!precision)
		return (arg);
	s = add_padding_uint(arg, precision, "0");
	return (s);
}

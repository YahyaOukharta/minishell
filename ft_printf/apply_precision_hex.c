/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:50:45 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/06 22:51:14 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char	*add_precision_hex(char *arg, char *precision)
{
	char *s;

	if (!precision)
		return (arg);
	s = add_padding_hex(arg, precision, "0");
	return (s);
}

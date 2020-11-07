/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:36:40 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/06 22:37:39 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char	*add_precision_c(char *arg, char *precision)
{
	char	*s;

	(void)precision;
	s = ft_strdup(arg);
	free(arg);
	return (s);
}

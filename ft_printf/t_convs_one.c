/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_convs_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:58:43 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:58:44 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_convs.h"

char	*get_char_arg(va_list args)
{
	char	*s;

	s = ft_calloc(2, 1);
	s[0] = va_arg(args, int);
	return (s);
}

char	*get_string_arg(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	return (s ? ft_strdup(s) : ft_strdup("(null)"));
}

char	*get_pointer_arg(va_list args)
{
	char	*s;

	s = ft_itoa_base(va_arg(args, unsigned long long), "0123456789abcdef");
	return (s ? s : ft_strdup("(nil)"));
}

char	*get_dec_arg(va_list args)
{
	return (ft_itoa(va_arg(args, int)));
}

char	*get_int_arg(va_list args)
{
	return (ft_itoa(va_arg(args, int)));
}

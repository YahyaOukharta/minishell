/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_convs_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:58:50 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:58:53 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_convs.h"

char	*get_uint_arg(va_list args)
{
	return (ft_utoa(va_arg(args, unsigned int)));
}

char	*get_hex_arg(va_list args)
{
	return (ft_itoa_base(va_arg(args, unsigned int), "0123456789abcdef"));
}

char	*get_uppercase_hex_arg(va_list args)
{
	return (ft_itoa_base(va_arg(args, unsigned int), "0123456789ABCDEF"));
}

char	*get_percent_sign(va_list args)
{
	char	*s;

	(void)args;
	s = ft_calloc(2, 1);
	s[0] = '%';
	return (s);
}

void	init_t_dispatcher(void)
{
	g_t_dispatcher[0] = get_char_arg;
	g_t_dispatcher[1] = get_string_arg;
	g_t_dispatcher[2] = get_pointer_arg;
	g_t_dispatcher[3] = get_int_arg;
	g_t_dispatcher[4] = get_int_arg;
	g_t_dispatcher[5] = get_uint_arg;
	g_t_dispatcher[6] = get_hex_arg;
	g_t_dispatcher[7] = get_uppercase_hex_arg;
	g_t_dispatcher[8] = get_percent_sign;
}

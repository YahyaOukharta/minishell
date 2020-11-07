/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_dispatcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:44:48 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:46:45 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "min_width.h"

void	init_w_dispatcher(void)
{
	g_w_dispatcher[0] = add_padding_char;
	g_w_dispatcher[1] = add_padding_string;
	g_w_dispatcher[2] = add_padding_ptr;
	g_w_dispatcher[3] = add_padding_int;
	g_w_dispatcher[4] = add_padding_int;
	g_w_dispatcher[5] = add_padding_uint;
	g_w_dispatcher[6] = add_padding_hex;
	g_w_dispatcher[7] = add_padding_hex;
	g_w_dispatcher[8] = add_padding_percent_sign;
}

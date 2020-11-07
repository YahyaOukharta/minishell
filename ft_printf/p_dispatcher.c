/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dispatcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:37:57 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:49:31 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

void	init_p_dispatcher(void)
{
	g_p_dispatcher[0] = add_precision_c;
	g_p_dispatcher[1] = add_precision_s;
	g_p_dispatcher[2] = add_precision_ptr;
	g_p_dispatcher[3] = add_precision_int;
	g_p_dispatcher[4] = add_precision_int;
	g_p_dispatcher[5] = add_precision_uint;
	g_p_dispatcher[6] = add_precision_hex;
	g_p_dispatcher[7] = add_precision_hex;
	g_p_dispatcher[8] = add_precision_percent_sign;
}

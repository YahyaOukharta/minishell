/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_convs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:04:28 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:04:32 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CONVS_H
# define T_CONVS_H
# include "ft_printf.h"

char *get_char_arg(va_list args);
char *get_string_arg(va_list args);
char *get_pointer_arg(va_list args);
char *get_int_arg(va_list args);
char *get_uint_arg(va_list args);
char *get_hex_arg(va_list args);
char *get_uppercase_hex_arg(va_list args);
void init_t_dispatcher(void);
typedef char*(*t_t_disp)(va_list);
t_t_disp g_t_dispatcher[9];
#endif

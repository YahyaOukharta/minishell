/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_width.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:35:46 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 13:36:26 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIN_WIDTH_H
# define MIN_WIDTH_H
# include "ft_printf.h"

char	*add_unsigned_padding(char *arg, size_t w, size_t v_len, char flag);
char	*add_padding_char(char *arg, char *width, const char *flags);
char	*add_padding_string(char *arg, char *width, const char *flags);
char	*add_padding_ptr(char *arg, char *width, const char *flags);
char	*add_padding_int(char *arg, char *width, const char *flags);
char	*add_padding_uint(char *arg, char *width, const char *flags);
char	*add_padding_hex(char *arg, char *width, const char *flags);
char	*add_padding_percent_sign(char *arg, char *width, const char *flags);
char	get_active_flag(const char *flags);
void	init_w_dispatcher(void);
typedef char*(*t_w_disp)(char *, char *, const char *);
t_w_disp g_w_dispatcher[9];
#endif

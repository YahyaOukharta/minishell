/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specifiers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:06:08 by youkhart          #+#    #+#             */
/*   Updated: 2019/11/07 14:06:12 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_SPECIFIERS_H
# define GET_SPECIFIERS_H
# include "ft_printf.h"

char *get_conv(char *start, const char *t_convs);
char *get_flags(char *conv, const char *flags);
char *get_precision(char *conv, const char *t_convs);
char *get_min_width(char *conv, const char *flags);
#endif

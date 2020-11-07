/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:46:53 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/28 17:36:21 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define MAX_INT 2147483647

int		check(int fd, char **line, size_t bufsize);
size_t	ft_strlen(const char *str);
void	*ft_memchr(const void *ptr, int c, size_t n);
char	*realloc_concat(char *s1, char *buf, size_t bufsize);
int		read_file(int fd, char **line, char *buf, char **remainder);
int		get_next_line(int fd, char **line);
#endif

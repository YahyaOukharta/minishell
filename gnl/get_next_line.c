/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:46:14 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/28 17:42:47 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf;
	char			*endl;
	char			*tmp;

	if (check(fd, line, BUFFER_SIZE) || !(buf = (char *)malloc(BUFFER_SIZE)))
		return (-1);
	*line = realloc_concat(NULL, "", 0);
	if (remainder)
	{
		endl = ft_memchr(remainder, '\n', ft_strlen(remainder));
		if (endl)
			*endl = '\0';
		*line = realloc_concat(*line, remainder, ft_strlen(remainder));
		tmp = (endl ? realloc_concat(NULL, endl + 1, ft_strlen(endl + 1)) : 0);
		free(remainder);
		remainder = tmp;
		if (endl)
		{
			free(buf);
			return (1);
		}
	}
	return (read_file(fd, line, buf, &remainder));
}

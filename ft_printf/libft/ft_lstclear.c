/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <youkhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 08:39:38 by youkhart          #+#    #+#             */
/*   Updated: 2019/12/26 08:39:41 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*loop;
	t_list		*temp;

	loop = *lst;
	while (loop)
	{
		del(loop->content);
		temp = loop->next;
		free(loop);
		loop = temp;
	}
	(*lst) = NULL;
}

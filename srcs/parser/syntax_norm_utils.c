/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_norm_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:55:48 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/15 12:14:53 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_multiple(char *s, int pos)
{
	if (check_pipeline(s) == 0)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", s + pos);
		return (0);
	}
	return (1);
}

int			check_quotes_norm(char *s, int *pos)
{
	if (check_quotes(s, pos) == 0)
	{
		if (s[*pos + 1] == '\0')
			ft_printf("minishell: unexpected EOF while looking for matching `%c'\n", s[*pos]);
		else
			ft_printf("minishell: syntax error near unexpected token `%s'\n", s + *pos);
		return (0);
	}
	return (1);
}

int			check_pipe_norm(char *s)
{
	if (check_pipe(s) == 0)
	{
		ft_printf("minishell: minishell: syntax error near unexpected token %s\n", ft_strchr(s, '|'));
		return (0);
	}
	return (1);
}

int			check_redir_norm(char *s)
{
	char	*e;

	e = NULL;
	if (check_redir(s) == 0)
	{
		e = ft_strnstr(s, ">", (ft_strlen(s) < 3 ? 3 : ft_strlen(s)));
		ft_printf("minishell: syntax error near unexpected token `%s'\n", e);
		return (0);
	}
	return (1);
}

int			check_syntax(char *s)
{
	int		pos;

	pos = 0;
	if (ft_strsearch(s, ';'))
		if (check_multiple(s, pos) == 0)
			return (0);
	if (ft_strchr(s, '\"') || ft_strchr(s, '\''))
		if (check_quotes_norm(s, &pos) == 0)
			return (0);
	if (ft_strsearch(s, '|'))
		if (check_pipe_norm(s) == 0)
			return (0);
	if (ft_strchr(s, '>') || ft_strchr(s, '<') || ft_strnstr(s, ">>",
		(ft_strlen(s) < 3 ? 3 : ft_strlen(s))))
		if (check_redir_norm(s) == 0)
			return (0);
	return (1);
}

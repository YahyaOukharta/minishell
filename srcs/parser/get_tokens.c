/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:28:43 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/30 15:24:33 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			quote_ends(char *s, char c)
{
	int	i;

	i = 0;
	if (QUOTE(s[i]) && i == 0)
		return (1);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

void		fill_redir(t_redir *redir, char *s, int *i, int in)
{
	if (in == 0 && ((s[*i] == '>' && s[*i + 1] == '>') ||
			s[*i] == '>' || s[*i] == '<'))
	{
		if (s[*i] == '>' && s[*i + 1] == '>')
			redir->outs = realloc__(redir->outs, get_rarg(s + *i, i));
		else if (s[*i] == '>')
			redir->outs = realloc__(redir->outs, get_rarg(s + *i, i));
		else
			redir->ins = realloc__(redir->ins, get_rarg(s + *i, i));
		if ((size_t)i < ft_strlen(s) &&
		s[*i] != '\0' && ((s[*i] == ' ' || s[*i + 1] == '\0')
				&& s[*i] != '>' && s[*i] != '<'))
			*i += 1;
	}
}

void		quote_token(char *s, int *i, t_redir *redir)
{
	*i += 1;
	redir->tokens = realloc__(redir->tokens,
		inside_quotes(s + *i, i, s[*i - 1]));
	if ((size_t)*i < ft_strlen(s))
		*i -= 1;
	if ((size_t)*i < ft_strlen(s) && QUOTE(s[*i]) && s[*i + 1] != '\0')
		*i += 1;
}

void		inc_(int *i, char *s)
{
	if ((size_t)*i < ft_strlen(s) &&
	s[*i] != '\0' && (s[*i] == ' ' || s[*i + 1] == '\0')
	&& s[*i] != '>' && s[*i] != '<')
		*i += 1;
}

void		init_redir(t_redir *redir)
{
	redir->ins = NULL;
	redir->outs = NULL;
	redir->tokens = NULL;
}

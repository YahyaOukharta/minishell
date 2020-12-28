/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:52:34 by malaoui           #+#    #+#             */
/*   Updated: 2020/12/28 17:09:22 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_cmds(t_command **cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i]->tokens)
			free_s_tab(cmd[i]->tokens);
		if (cmd[i]->input_files)
			free_s_tab(cmd[i]->input_files);
		if (cmd[i]->output_files)
			free_s_tab(cmd[i]->output_files);
		free(cmd[i]);
		i++;
	}
	free(cmd[i]);
	free(cmd);
}

int			no_alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]))
			return (0);
		if (s[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

void		free_pipeline(t_pipeline **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		if (p[i]->cmds)
			free_cmds(p[i]->cmds);
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:50:06 by youkhart          #+#    #+#             */
/*   Updated: 2020/12/27 15:50:10 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*g_children;

void	wait_for_children(t_pipeline *p)
{
	int	i;

	i = 0;
	while (i < p->n_commands)
	{
		if (g_children[i])
			while (g_children[i] != waitpid(
				g_children[i], &g_status, WUNTRACED))
				;
		i++;
	}
}

int		execute_pipeline(t_pipeline *pipeline)
{
	int		i;
	int		fd[2];
	int		in;
	int		out;

	i = 0;
	in = 0;
	g_children = (int *)malloc(sizeof(int) * pipeline->n_commands);
	ft_bzero(g_children, sizeof(int) * pipeline->n_commands);
	while (i < (pipeline->n_commands) - 1)
	{
		pipe(fd);
		out = fd[1];
		g_status = redirect_outputs(pipeline->cmds[i], in, out);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	out = 1;
	g_status = redirect_outputs(pipeline->cmds[i], in, out);
	wait_for_children(pipeline);
	free(g_children);
	return (g_status % 255);
}

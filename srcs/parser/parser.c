/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:07 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/20 16:25:37 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*new_cmd(char *line)
{
	t_command	*cmd;
	t_redir		redir;

	cmd = (t_command *)malloc(sizeof(t_command));
	redir = get_tokens(line);
	cmd->tokens = redir.tokens;
	cmd->input_files = redir.ins;
	cmd->output_files = redir.outs;
	return (cmd);
}

t_pipeline		*new_pipeline(char **lines)
{
	t_pipeline	*pipeline;
	int			i;

	pipeline = (t_pipeline *)malloc(sizeof(t_pipeline));
	pipeline->cmds = (t_command **)malloc(
		sizeof(t_command *) * (tab_len(lines) + 1));
	i = -1;
	while (lines[++i])
		pipeline->cmds[i] = new_cmd(lines[i]);
	pipeline->cmds[i] = 0;
	pipeline->n_commands = i;
	return (pipeline);
}

char			*expand_env(char *s)
{
	char *tmp;

	if (ft_strchr(s, '$'))
	{
		tmp = s;
		s = ft_env(tmp);
		free(tmp);
	}
	return (s);
}

t_pipeline		**parser(char *line)
{
	char		**pipelines;
	t_pipeline	**parsed_line;
	int			i;
	char		**split;

	line = ft_strtrim(line, " \t");
	pipelines = parser_split(line, ';');
	parsed_line = (t_pipeline **)malloc(
		sizeof(t_pipeline*) * (tab_len(pipelines) + 1));
	i = -1;
	while (pipelines[++i] != NULL)
	{
		pipelines[i] = expand_env(pipelines[i]);
		split = parser_split(pipelines[i], '|');
		parsed_line[i] = new_pipeline(split);
		free_s_tab(split);
		if (parsed_line[i]->cmds && g_status != -1)
			g_status = execute_pipeline(parsed_line[i]);
	}
	free(line);
	free_s_tab(pipelines);
	parsed_line[i] = 0;
	return (parsed_line);
}

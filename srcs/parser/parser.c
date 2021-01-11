/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:07 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/10 17:24:41 by malaoui          ###   ########.fr       */
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

t_pipeline		**parser(char *line)
{
	char		**pipelines;
	t_pipeline	**parsed_line;
	int			i;
	char		**split;

	split = NULL;
	line = ft_strtrim(line, " \t");
	pipelines = parser_split(line, ';');
	parsed_line = (t_pipeline **)malloc(
		sizeof(t_pipeline*) * (tab_len(pipelines) + 1));
	i = 0;
	while (pipelines[i] != NULL)
	{
		pipelines[i] = ft_env(pipelines[i]);
		split = parser_split(pipelines[i], '|');
		parsed_line[i] = new_pipeline(split);
		if (parsed_line[i]->cmds)
			g_status = execute_pipeline(parsed_line[i]);
		free(pipelines[i]);
		free_s_tab(split);
		i++;
	}
	free(line);
	free(pipelines);
	parsed_line[i] = 0;
	return (parsed_line);
}

void			print_parsed_line(t_pipeline **parsed_line)
{
	int i;
	int j;
	int k;

	i = 0;
	if (parsed_line)
	{
		while (parsed_line[i])
		{
			j = 0;
			ft_printf("***Pipeline %d ***\n" ,i+1 );
			if (parsed_line[i]->cmds)
			{
				while (parsed_line[i]->cmds[j])
				{
					ft_printf("\t**** Command %d ****\n", j + 1);
					k=0;
					ft_printf("\t  Tokens : ");
					if (parsed_line[i]->cmds[j]->tokens)
					{
						while (parsed_line[i]->cmds[j]->tokens[k])
						{
							ft_printf("|%s| ",parsed_line[i]->cmds[j]->tokens[k]);
							k++;
						}
					}
					ft_printf("\n");
					k=0;
					ft_printf("\t  Inputs : ");
					if (parsed_line[i]->cmds[j]->input_files)
					{
						while (parsed_line[i]->cmds[j]->input_files[k])
						{
							if ((parsed_line[i]->cmds[j]->input_files[k]) != NULL)
								ft_printf("%s ",parsed_line[i]->cmds[j]->input_files[k]);
							k++;
						}
					}
					ft_printf("\n");
					k=0;
					ft_printf("\t  Outputs : ");
					if (parsed_line[i]->cmds[j]->output_files)
					{
						while (parsed_line[i]->cmds[j]->output_files[k])
						{	
							ft_printf("%s ",parsed_line[i]->cmds[j]->output_files[k]);
							k++;
						}
					}
					ft_printf("\n");
					j++;
				}
			}
			i++;
		}
	}
	//ft_printf("\n");
}

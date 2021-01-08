/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaoui <malaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:53:07 by malaoui           #+#    #+#             */
/*   Updated: 2021/01/08 15:03:15 by malaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*matching_key(char *s)
{
	int 	i;
	int 	len;
	char 	*key;

	i = 0;
	len = ft_strlen(s);
	key = NULL;
	while (i < len)
	{
		if (s[i] == '*')
			return (key);
		key = append(key, s[i++]);
	}
	key[i] = '\0';
	return (key);
}

char			**matched(char **s, char *str, int pos)
{
	int 		i;
	char		*key;
	struct dirent	**namelist;
	int 		n;

	i = 0;
	key = matching_key(str);	
	n = scandir(".", &namelist, NULL, alphasort);
	if (n < 0)
        perror("scandir");
    else
	{
		while (i < n)
		{
			if (namelist[i])
			{
				if (namelist[i]->d_name[0] == '.')
				{
					free(namelist[i]);
					i++;
					continue ;
				}
				if (ft_strlen(namelist[i]->d_name) && !ft_strncmp(namelist[i]->d_name, key, ft_strlen(key)))
					s = realloc__(s, namelist[i]->d_name, tab_len(s));
				free(namelist[i]);
			}
			i++;
		}
		free(namelist);
	}
	return (s);
}

char			**filter_str(int i, char **str)
{
	char			*tmp;
	int				c;
	char			**match;

	c = -1;
	tmp = NULL;
	match = (char **)malloc(sizeof(char *) * (i + 1));
	while (++c < i)
		match[c] = ft_strdup(str[c]);
    match[c] = NULL;
	match = matched(match, str[c], c);
	return (match);
}

char			**ft_filter(char **s)
{
	int			i;
	char		*p;
	char		**star;

	i = 0;
	p = NULL;
	star = realloc__(s, NULL, tab_len(s));
	while (i < tab_len(star))
	{
		if (ft_strsearch(star[i], '*'))
			star = filter_str(i, star);
		i++;
	}
	return (star);
}

t_command		*new_cmd(char *line)
{
	t_command	*cmd;
	t_redir		redir;

	cmd = (t_command *)malloc(sizeof(t_command));
	redir = get_tokens(line);
	cmd->tokens = ft_filter(redir.tokens);
	cmd->input_files = ft_filter(redir.ins);
	cmd->output_files = ft_filter(redir.outs);
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
		split = parser_split(pipelines[i], '|');
		parsed_line[i] = new_pipeline(split);
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
